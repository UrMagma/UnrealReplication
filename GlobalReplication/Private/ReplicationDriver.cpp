#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/Socket.h"
#include "GlobalReplication/Public/RPC.h"
#include <iostream>
#include <algorithm>

ReplicationDriver::ReplicationDriver()
{
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

void ReplicationDriver::HandleRPC(const std::vector<uint8_t>& RPCData)
{
    FMemoryArchive Ar(const_cast<std::vector<uint8_t>&>(RPCData), false);
    FRPCData RpcData;
    RpcData.Serialize(Ar);

    auto ObjIt = NetIDToObjectMap.find(RpcData.NetID);
    if (ObjIt == NetIDToObjectMap.end())
    {
        std::cerr << "HandleRPC: Object with NetID " << RpcData.NetID << " not found." << std::endl;
        return;
    }

    auto Thunk = RPCRegistry::Get().Find(RpcData.FunctionName);
    if (!Thunk)
    {
        std::cerr << "HandleRPC: RPC function " << RpcData.FunctionName << " not found." << std::endl;
        return;
    }

    Thunk(ObjIt->second, Ar);
}

void ReplicationDriver::Tick(float DeltaTime)
{
    // Receive incoming data
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
        std::vector<uint8_t> PacketData(RecvBuffer.begin() + 1, RecvBuffer.begin() + BytesRead);

        if (PacketType == EPacketType::RPC)
        {
            HandleRPC(PacketData);
        }
        else
        {
            std::cout << "Received property update (not implemented yet)" << std::endl;
        }
    }

    // Replicate objects and send RPCs
    for (auto& Pair : Connections)
    {
        auto& Conn = Pair.second;
        const auto& ReplicatedObjects = static_cast<ReplicationConnection*>(Conn.get())->GetReplicatedObjects();

        std::vector<IReplicatedObject*> AllObjectsToReplicate;
        for (const auto& ObjPair : ReplicatedObjects)
        {
            AllObjectsToReplicate.push_back(ObjPair.second);
            for (auto* SubObj : ObjPair.second->SubObjects)
            {
                AllObjectsToReplicate.push_back(SubObj);
            }
        }

        std::vector<IReplicatedObject*> DirtyObjects;
        for (IReplicatedObject* Obj : AllObjectsToReplicate)
        {
            for(const auto* Prop : Obj->GetReplicatedProperties())
            {
                if (Prop->IsDirty())
                {
                    DirtyObjects.push_back(Obj);
                    break;
                }
            }
        }

        // Sort dirty objects by priority
        std::sort(DirtyObjects.begin(), DirtyObjects.end(), [](IReplicatedObject* A, IReplicatedObject* B) {
            return A->GetPriority() > B->GetPriority();
        });

        for (IReplicatedObject* Obj : DirtyObjects)
        {
            bool bHasDirtyProperty = false;
            std::vector<uint8_t> ObjectBuffer;
            FMemoryArchive Ar(ObjectBuffer, true); // true for saving

            const auto& Properties = Obj->GetReplicatedProperties();
            for(auto* Prop : Properties)
            {
                if (Prop->IsDirty())
                {
                    bHasDirtyProperty = true;
                    Prop->Serialize(Ar);
                    Prop->ClearDirty();
                }
            }

            if (bHasDirtyProperty)
            {
                std::vector<uint8_t> Packet;
                Packet.push_back((uint8_t)EPacketType::Property);
                Packet.insert(Packet.end(), ObjectBuffer.begin(), ObjectBuffer.end());
                Conn->SendData(ListenSocket, Packet);
                std::cout << "Replicated object " << Obj->GetNetID() << " with priority " << Obj->GetPriority() << " to connection." << std::endl;
            }
        }


        // Send queued RPCs
        auto& RPCBuffer = static_cast<ReplicationConnection*>(Conn.get())->GetOutgoingRPCBuffer();
        while(!RPCBuffer.empty())
        {
            auto& RPCData = RPCBuffer.front();
            std::vector<uint8_t> Packet;
            Packet.push_back((uint8_t)EPacketType::RPC);
            Packet.insert(Packet.end(), RPCData.begin(), RPCData.end());
            Conn->SendData(ListenSocket, Packet);
            RPCBuffer.pop();
        }
    }
}
