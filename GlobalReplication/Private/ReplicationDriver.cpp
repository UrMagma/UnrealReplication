#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/GlobalReplication.inl"
#include "GlobalReplication/Public/ReplicatedComponent.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/Socket.h"
#include "GlobalReplication/Public/RPC.h"
#include <iostream>
#include <algorithm>

#include "ReplicationInternals.h"


ReplicationDriver::ReplicationDriver()
{
    IReplicatedObject::RegisterBuiltInRPCs();
}

bool ReplicationDriver::Init(uint16_t Port)
{
    if (!ListenSocket.Create())
    {
        return false;
    }

    if (!ListenSocket.Bind("0.0.0.0", Port))
    {
        return false;
    }

    ListenSocket.SetNonBlocking(true);
    return true;
}

void ReplicationDriver::AddConnection(std::shared_ptr<IReplicationConnection> Conn)
{
    auto RC = std::static_pointer_cast<ReplicationConnection>(Conn);
    Connections[RC->GetAddress()] = Conn;
}

void ReplicationDriver::RemoveConnection(std::shared_ptr<IReplicationConnection> Conn)
{
    auto RC = std::static_pointer_cast<ReplicationConnection>(Conn);
    Connections.erase(RC->GetAddress());
}

void ReplicationDriver::RegisterObject(IReplicatedObject* Obj)
{
    if (Obj)
    {
        NetIDToObjectMap[Obj->GetNetID()] = Obj;
    }
}

void ReplicationDriver::SetObjectOwner(IReplicatedObject* Obj, std::shared_ptr<IReplicationConnection> NewOwner)
{
    if (!Obj)
    {
        return;
    }

    auto OldOwner = Obj->GetOwningConnection();

    if (OldOwner == NewOwner)
    {
        return; // No change
    }

    // Notify the old owner that they've lost authority
    if (OldOwner)
    {
        std::cout << "Notifying old owner of object " << Obj->GetNetID() << " that they lost ownership." << std::endl;
        Obj->CallRPC_OnClient("IReplicatedObject::Client_LostOwnership");
    }

    Obj->SetOwningConnection(NewOwner);

    // Notify the new owner that they've gained authority
    if (NewOwner)
    {
        std::cout << "Notifying new owner of object " << Obj->GetNetID() << " that they gained ownership." << std::endl;
        Obj->CallRPC_OnClient("IReplicatedObject::Client_GainedOwnership");
    }
    else
    {
        // Ownership is returning to the server
        std::cout << "Ownership of object " << Obj->GetNetID() << " returned to server." << std::endl;
    }
}

void ReplicationDriver::HandleRPC(const std::vector<uint8_t>& PacketData, std::shared_ptr<IReplicationConnection> SourceConnection)
{
    FMemoryArchive Ar(const_cast<std::vector<uint8_t>&>(PacketData), false);
    FRPCData RpcData;
    RpcData.Serialize(Ar);

    auto ObjIt = NetIDToObjectMap.find(RpcData.NetID);
    if (ObjIt == NetIDToObjectMap.end())
    {
        std::cerr << "HandleRPC: Object with NetID " << RpcData.NetID << " not found." << std::endl;
        return;
    }

    // Handle built-in RPCs separately
    if (RpcData.FunctionName == "IReplicatedObject::Server_RequestOwnership")
    {
        if (ObjIt->second->CanBeOwnedByClient())
        {
            SetObjectOwner(ObjIt->second, SourceConnection);
        }
        return;
    }

    auto Thunk = RPCRegistry::Get().Find(RpcData.FunctionName);
    if (!Thunk)
    {
        std::cerr << "HandleRPC: RPC function " << RpcData.FunctionName << " not found." << std::endl;
        return;
    }

    // The thunk expects an archive containing only the parameters.
    FMemoryArchive ParamArchive(RpcData.Parameters, false);
    Thunk(ObjIt->second, ParamArchive);
}

void ReplicationDriver::HandlePropertyUpdate(const std::vector<uint8_t>& PacketData)
{
    FMemoryArchive Ar(const_cast<std::vector<uint8_t>&>(PacketData), false);

    // 1. Deserialize the header
    FPropertyPacketHeader Header;
    Header.Serialize(Ar);

    // 2. Find the main object
    auto ObjIt = NetIDToObjectMap.find(Header.NetID);
    if (ObjIt == NetIDToObjectMap.end())
    {
        std::cerr << "HandlePropertyUpdate: Object with NetID " << Header.NetID << " not found." << std::endl;
        return;
    }
    IReplicatedObject* MainObj = ObjIt->second;

    // 3. Find the target object (main object or sub-object)
    FReplicatedObjectBase* TargetObj = nullptr;
    if (Header.SubObjectIndex == 0)
    {
        TargetObj = MainObj;
    }
    else
    {
        const auto& SubObjects = MainObj->GetSubObjects();
        uint8_t Index = Header.SubObjectIndex - 1; // 1-based index from packet
        if (Index < SubObjects.size())
        {
            TargetObj = SubObjects[Index];
        }
        else
        {
            std::cerr << "HandlePropertyUpdate: Invalid SubObjectIndex " << (int)Header.SubObjectIndex << std::endl;
            return;
        }
    }

    if (TargetObj)
    {
        // 4. Deserialize all properties into the target object
        for (auto* Prop : TargetObj->GetReplicatedProperties())
        {
            Prop->Serialize(Ar);
            // On the receiving end, we don't clear the dirty flag.
            // The flag is only cleared on the authoritative instance after sending.
        }
        std::cout << "Applied property update for object " << Header.NetID << ", sub-object " << (int)Header.SubObjectIndex << std::endl;
    }
}

void ReplicationDriver::Tick(float DeltaTime)
{
    // --- 1. Receive Incoming Data ---
    // Process all packets received on the socket since the last tick.
    std::vector<uint8_t> RecvBuffer(1024);
    sockaddr_in From;
    int32_t BytesRead = ListenSocket.RecvFrom(RecvBuffer, From);
    if (BytesRead > 0)
    {
        // Check if we already have a connection from this address
        if (Connections.find(From) == Connections.end())
        {
            // If not, create a new one
            auto NewConnection = std::make_shared<ReplicationConnection>(From);
            Connections[From] = NewConnection;
            std::cout << "Created new connection" << std::endl;

            if (OnNewConnection)
            {
                OnNewConnection(NewConnection);
            }
        }

        // Process the packet
        EPacketType PacketType = (EPacketType)RecvBuffer[0];
        auto Connection = Connections[From];
        std::vector<uint8_t> PacketData(RecvBuffer.begin() + 1, RecvBuffer.begin() + BytesRead);

        if (PacketType == EPacketType::RPC)
        {
            HandleRPC(PacketData, Connection);
        }
        else if (PacketType == EPacketType::Property)
        {
            HandlePropertyUpdate(PacketData);
        }
    }

    // --- 2. Send Outgoing Data ---
    // Iterate through all connections and send them any pending data.
    for (auto& Pair : Connections)
    {
        auto& Conn = Pair.second;
        const auto& ReplicatedObjects = static_cast<ReplicationConnection*>(Conn.get())->GetReplicatedObjects();

        // TODO: Add priority sorting back in
        std::vector<FReplicatedObjectBase*> AllObjectsToReplicate;
        for (const auto& ObjPair : ReplicatedObjects)
        {
            AllObjectsToReplicate.push_back(ObjPair.second);
            for (auto* SubObj : ObjPair.second->GetSubObjects())
            {
                AllObjectsToReplicate.push_back(SubObj);
            }
        }

        // --- 2a. Replicate Dirty Properties ---
        // --- 2a. Replicate Dirty Properties ---
        for (FReplicatedObjectBase* ObjBase : AllObjectsToReplicate)
        {
            // Check if the object has any dirty properties
            bool bHasDirtyProperty = false;
            for (const auto* Prop : ObjBase->GetReplicatedProperties())
            {
                if (Prop->IsDirty())
                {
                    bHasDirtyProperty = true;
                    break;
                }
            }

            if (bHasDirtyProperty)
            {
                // Create the header
                FPropertyPacketHeader Header;
                UReplicatedComponent* Comp = dynamic_cast<UReplicatedComponent*>(ObjBase);
                if (Comp)
                {
                    Header.NetID = Comp->GetOwner()->GetNetID();
                    Header.SubObjectIndex = Comp->GetSubObjectIndex();
                }
                else
                {
                    IReplicatedObject* MainObj = static_cast<IReplicatedObject*>(ObjBase);
                    Header.NetID = MainObj->GetNetID();
                    Header.SubObjectIndex = 0;
                }

                // Serialize the dirty properties
                std::vector<uint8_t> PropertyData;
                FMemoryArchive Ar(PropertyData, true);
                for (auto* Prop : ObjBase->GetReplicatedProperties())
                {
                    if (Prop->IsDirty())
                    {
                        Prop->Serialize(Ar);
                        Prop->ClearDirty();
                    }
                }

                // Create the final packet and send it
                std::vector<uint8_t> Packet;
                Packet.push_back((uint8_t)EPacketType::Property);

                // Serialize the header into the packet
                std::vector<uint8_t> HeaderData;
                FMemoryArchive HeaderAr(HeaderData, true);
                Header.Serialize(HeaderAr);
                Packet.insert(Packet.end(), HeaderData.begin(), HeaderData.end());

                // Add the property data
                Packet.insert(Packet.end(), PropertyData.begin(), PropertyData.end());

                Conn->SendData(ListenSocket, Packet);
                std::cout << "Replicated properties for object " << Header.NetID << ", sub-object " << (int)Header.SubObjectIndex << std::endl;
            }
        }


        // --- 2b. Send Queued RPCs ---
        auto& RPCBuffer = static_cast<ReplicationConnection*>(Conn.get())->GetOutgoingRPCBuffer();
        while(!RPCBuffer.empty())
        {
            FRPCData& RpcData = RPCBuffer.front();

            // Serialize the FRPCData struct into a buffer
            std::vector<uint8_t> RpcPayload;
            FMemoryArchive Ar(RpcPayload, true);
            RpcData.Serialize(Ar);

            // Prepend the packet type and send
            std::vector<uint8_t> Packet;
            Packet.push_back((uint8_t)EPacketType::RPC);
            Packet.insert(Packet.end(), RpcPayload.begin(), RpcPayload.end());
            Conn->SendData(ListenSocket, Packet);

            RPCBuffer.pop();
        }
    }
}
