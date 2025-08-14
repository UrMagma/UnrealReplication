#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/ReplicatedProperty.h"
#include "GlobalReplication/Public/Socket.h"
#include "GlobalReplication/Public/RPC.h"
#include "GlobalReplication/Public/ReplicatedComponent.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <thread>
#include <atomic>
#include <functional>

class MyTestComponent : public UReplicatedComponent
{
public:
    MyTestComponent(IReplicatedObject* InOwner, uint64_t InNetID)
        : UReplicatedComponent(InOwner)
    {
        NetID = InNetID;
        RegisterReplicatedProperties();
    }

    void RegisterReplicatedProperties() override
    {
        ReplicatedProperties.push_back(&CompHealth);
    }

    uint64_t GetNetID() const override { return NetID; }
    float GetPriority() const override { return 1.0f; }
    bool HasAuthority() const override { return GetOwner()->HasAuthority(); }

    FRepProperty<int> CompHealth = 100;
private:
    uint64_t NetID;
};

// A simple replicated object for demonstration
class MyReplicatedObject : public IReplicatedObject
{
public:
    MyReplicatedObject(uint64_t InNetID = 0, bool bInHasAuthority = false)
        : bHasAuthority(bInHasAuthority)
    {
        NetID = InNetID;
        TestComponent = new MyTestComponent(this, NetID + 1);
        RegisterReplicatedProperties();
        RegisterReplicatedSubObjects();
    }

    ~MyReplicatedObject()
    {
        delete TestComponent;
    }

    void RegisterReplicatedProperties() override
    {
        ReplicatedProperties.push_back(&NetID);
    }

    void RegisterReplicatedSubObjects() override
    {
        AddComponent(TestComponent);
    }

    uint64_t GetNetID() const override { return NetID; }
    float GetPriority() const override { return 1.0f; }
    bool HasAuthority() const override { return bHasAuthority; }

    MyTestComponent* TestComponent;
    FRepProperty<uint64_t> NetID = 0;
    bool bHasAuthority;
};


// Global state to coordinate the test
std::atomic<bool> bServerShouldStop = false;

// Server logic
void RunServer(ReplicationDriver& Driver)
{
    while (!bServerShouldStop)
    {
        Driver.Tick(0.016f);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    std::cout << "[Server] Shutting down." << std::endl;
}

// Client logic
void RunClient(FSocket& ClientSocket)
{
    // Send a "hello" message to the server
    std::vector<uint8_t> HelloMessage = { 'h', 'e', 'l', 'l', 'o' };
    ClientSocket.SendTo(HelloMessage, "127.0.0.1", 8888);
    std::cout << "[Client] Sent hello message." << std::endl;
}

int main()
{
    std::cout << "--- GlobalReplication Sub-object Test ---" << std::endl;

    // 1. Create a replicated object on the server
    MyReplicatedObject ServerObj(101, true); // Has authority
    std::cout << "[Server] Created object " << ServerObj.GetNetID() << std::endl;
    std::cout << "[Server] Created sub-object " << ServerObj.TestComponent->GetNetID() << std::endl;


    // 2. Create and initialize the server driver
    ReplicationDriver Driver;
    Driver.RegisterObject(&ServerObj); // Register the object with the driver
    Driver.RegisterObject(ServerObj.TestComponent); // Register the sub-object

    Driver.OnNewConnection = [&](std::shared_ptr<IReplicationConnection> NewConn)
    {
        std::cout << "[Server] New connection established. Adding object to replication list." << std::endl;
        NewConn->AddReplicatedObject(&ServerObj);
    };

    if (!Driver.Init(8888))
    {
        return 1;
    }
    std::cout << "[Server] Listening on port 8888" << std::endl;

    // 3. Create the client socket
    FSocket ClientSocket;
    if (!ClientSocket.Create())
    {
        return 1;
    }

    // 4. Run the server and client in separate threads
    std::thread ServerThread(RunServer, std::ref(Driver));
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give server time to start
    std::thread ClientThread(RunClient, std::ref(ClientSocket));

    // 5. Wait for the test to complete
    std::this_thread::sleep_for(std::chrono::seconds(1));
    bServerShouldStop = true;
    ServerThread.join();
    ClientThread.join();

    std::cout << "\n--- Test Complete ---" << std::endl;

    return 0;
}
