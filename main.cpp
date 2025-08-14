#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/ReplicatedProperty.h"
#include "GlobalReplication/Public/Socket.h"
#include "GlobalReplication/Public/RPC.h"
#include "GlobalReplication/Public/ReplicatedComponent.h"
#include "GlobalReplication/Private/ReplicationInternals.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <thread>
#include <atomic>
#include <functional>

// A simple replicated object for demonstration
class MyReplicatedObject : public IReplicatedObject
{
public:
    MyReplicatedObject(uint64_t InNetID = 0)
    {
        NetID = InNetID;
        RegisterReplicatedProperties();

        // Register our RPCs
        REGISTER_RPC(MyReplicatedObject, Server_UpdatePlayerMessage);
    }

    void RegisterReplicatedProperties() override
    {
        ReplicatedProperties.push_back(&NetID);
        ReplicatedProperties.push_back(&PlayerName);
        ReplicatedProperties.push_back(&LastMessage);
    }

    // --- RPC Definition ---
    // This is the function that will be executed on the authoritative instance.
    void Server_UpdatePlayerMessage(const FString& NewMessage, int32_t SomeValue)
    {
        std::cout << "[RPC EXEC] Server_UpdatePlayerMessage called on object " << (uint64_t)NetID << std::endl;
        std::cout << "           NewMessage: " << NewMessage.ToString().c_str() << std::endl;
        std::cout << "           SomeValue: " << SomeValue << std::endl;
        LastMessage = NewMessage;
    }

    // Override the built-in ownership RPCs to react to changes
    void Client_GainedOwnership() override
    {
        std::cout << "[Object " << (uint64_t)NetID << "] I have gained ownership!" << std::endl;
        bHasAuthority = true;
    }

    void Client_LostOwnership() override
    {
        std::cout << "[Object " << (uint64_t)NetID << "] I have lost ownership." << std::endl;
        bHasAuthority = false;
    }

    uint64_t GetNetID() const override { return NetID; }
    float GetPriority() const override { return 1.0f; }
    bool HasAuthority() const override { return bHasAuthority; }

    void Print() const
    {
        std::cout << "  NetID: " << (uint64_t)NetID << std::endl;
        std::cout << "  PlayerName: " << ((FString)PlayerName).ToString().c_str() << std::endl;
        std::cout << "  LastMessage: " << ((FString)LastMessage).ToString().c_str() << std::endl;
    }

    bool bHasAuthority = false;
    FRepProperty<uint64_t> NetID;
    FRepProperty<FString> PlayerName;
    FRepProperty<FString> LastMessage;
};

// A replicated component for demonstration
class MyPlayerStatsComponent : public UReplicatedComponent
{
public:
    MyPlayerStatsComponent(IReplicatedObject* InOwner) : UReplicatedComponent(InOwner)
    {
        RegisterReplicatedProperties();
    }

    void RegisterReplicatedProperties() override
    {
        ReplicatedProperties.push_back(&Health);
        ReplicatedProperties.push_back(&Stamina);
    }

    void Print() const
    {
        std::cout << "    Health: " << (int)Health << ", Stamina: " << (int)Stamina << std::endl;
    }

    FRepProperty<int32_t> Health = 100;
    FRepProperty<int32_t> Stamina = 100;
};

// This is a dummy driver class for testing purposes.
class TestReplicationDriver : public ReplicationDriver
{
public:
    void TestHandlePropertyUpdate(const std::vector<uint8_t>& PacketData)
    {
        HandlePropertyUpdate(PacketData);
    }
};


int main()
{
    std::cout << "--- Sub-Object Replication Test ---" << std::endl;

    // 1. Create a "server-side" object and its component
    MyReplicatedObject ServerObject(101);
    MyPlayerStatsComponent ServerStats(&ServerObject);
    ServerObject.AddComponent(&ServerStats);

    // Change some properties
    ServerObject.PlayerName = "ServerJules";
    ServerStats.Health = 50;
    ServerStats.Stamina = 75;

    std::cout << "\n[Server] Initial state:" << std::endl;
    ServerObject.Print();
    ServerStats.Print();

    // 2. Manually create a property update packet for the main object
    std::vector<uint8_t> ServerObjectPacket;
    {
        FPropertyPacketHeader Header;
        Header.NetID = ServerObject.GetNetID();
        Header.SubObjectIndex = 0;

        std::vector<uint8_t> HeaderData, PropertyData;
        FMemoryArchive HeaderAr(HeaderData, true);
        Header.Serialize(HeaderAr);

        FMemoryArchive PropertyAr(PropertyData, true);
        for(auto* Prop : ServerObject.GetReplicatedProperties()) Prop->Serialize(PropertyAr);

        ServerObjectPacket.push_back((uint8_t)EPacketType::Property);
        ServerObjectPacket.insert(ServerObjectPacket.end(), HeaderData.begin(), HeaderData.end());
        ServerObjectPacket.insert(ServerObjectPacket.end(), PropertyData.begin(), PropertyData.end());
    }

    // 3. Manually create a property update packet for the component
    std::vector<uint8_t> ServerCompPacket;
    {
        FPropertyPacketHeader Header;
        Header.NetID = ServerObject.GetNetID();
        Header.SubObjectIndex = ServerStats.GetSubObjectIndex() + 1;

        std::vector<uint8_t> HeaderData, PropertyData;
        FMemoryArchive HeaderAr(HeaderData, true);
        Header.Serialize(HeaderAr);

        FMemoryArchive PropertyAr(PropertyData, true);
        for(auto* Prop : ServerStats.GetReplicatedProperties()) Prop->Serialize(PropertyAr);

        ServerCompPacket.push_back((uint8_t)EPacketType::Property);
        ServerCompPacket.insert(ServerCompPacket.end(), HeaderData.begin(), HeaderData.end());
        ServerCompPacket.insert(ServerCompPacket.end(), PropertyData.begin(), PropertyData.end());
    }

    // 4. Create a "client-side" object and driver
    TestReplicationDriver ClientDriver;
    MyReplicatedObject ClientObject(101);
    MyPlayerStatsComponent ClientStats(&ClientObject);
    ClientObject.AddComponent(&ClientStats);
    ClientDriver.RegisterObject(&ClientObject);

    std::cout << "\n[Client] Initial state:" << std::endl;
    ClientObject.Print();
    ClientStats.Print();

    // 5. Process the packets on the client driver
    std::cout << "\n[Client] Applying property updates..." << std::endl;
    ClientDriver.TestHandlePropertyUpdate(std::vector<uint8_t>(ServerObjectPacket.begin() + 1, ServerObjectPacket.end()));
    ClientDriver.TestHandlePropertyUpdate(std::vector<uint8_t>(ServerCompPacket.begin() + 1, ServerCompPacket.end()));

    // 6. Verification
    std::cout << "\n[Client] Final state:" << std::endl;
    ClientObject.Print();
    ClientStats.Print();

    std::cout << "\n--- Verification ---" << std::endl;
    bool bSuccess = true;
    if ((FString)ServerObject.PlayerName != (FString)ClientObject.PlayerName) bSuccess = false;
    if ((int32_t)ServerStats.Health != (int32_t)ClientStats.Health) bSuccess = false;
    if ((int32_t)ServerStats.Stamina != (int32_t)ClientStats.Stamina) bSuccess = false;

    if (bSuccess)
    {
        std::cout << "SUCCESS: All properties replicated correctly." << std::endl;
    }
    else
    {
        std::cout << "FAILED: Property mismatch after replication." << std::endl;
        return 1;
    }

    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}
