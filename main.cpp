#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/ReplicatedProperty.h"
#include "GlobalReplication/Public/Socket.h"
#include "GlobalReplication/Public/RPC.h"
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

// This is a dummy driver class for testing purposes.
// It gives us direct access to the HandleRPC method.
class TestReplicationDriver : public ReplicationDriver
{
public:
    void TestHandleRPC(const std::vector<uint8_t>& PacketData)
    {
        HandleRPC(PacketData);
    }
};


int main()
{
    std::cout << "--- RPC with Parameters Test ---" << std::endl;

    // 1. Create a "server-side" object instance. This is the one that has authority.
    MyReplicatedObject ServerObject(101);
    ServerObject.bHasAuthority = true;
    ServerObject.PlayerName = "Jules";
    ServerObject.LastMessage = "Initial";

    std::cout << "\n[Server] Initial state:" << std::endl;
    ServerObject.Print();

    // 2. Create a "client-side" representation of the object.
    MyReplicatedObject ClientObject(101);
    ClientObject.bHasAuthority = false;

    // 3. Simulate the client calling the RPC.
    FString MessageToSend = "Hello from the client!";
    int32_t ValueToSend = 42;

    std::vector<uint8_t> ParamBuffer;
    FMemoryArchive SaveParamsArchive(ParamBuffer, true);
    SaveParamsArchive << MessageToSend << ValueToSend;

    FRPCData RpcData;
    RpcData.NetID = ClientObject.GetNetID();
    RpcData.FunctionName = "MyReplicatedObject::Server_UpdatePlayerMessage";
    RpcData.Parameters = ParamBuffer;

    std::vector<uint8_t> PacketPayload;
    FMemoryArchive SavePacketArchive(PacketPayload, true);
    RpcData.Serialize(SavePacketArchive);

    std::cout << "\n[Client] Calling RPC with message: '" << MessageToSend.ToString().c_str() << "' and value: " << ValueToSend << std::endl;

    // 4. The server's driver receives this payload and processes it.
    TestReplicationDriver Driver;
    Driver.RegisterObject(&ServerObject);
    Driver.TestHandleRPC(PacketPayload);

    // 5. Verify the state of the server object was changed by the RPC.
    std::cout << "\n[Server] Final state:" << std::endl;
    ServerObject.Print();

    std::cout << "\n--- Verification ---" << std::endl;
    if (((FString)ServerObject.LastMessage) == MessageToSend)
    {
        std::cout << "SUCCESS: The RPC was executed correctly." << std::endl;
    }
    else
    {
        std::cout << "FAILED: The RPC did not modify the server state." << std::endl;
        return 1;
    }

    std::cout << "\n--- Test Complete ---" << std::endl;
    return 0;
}
