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
    }

    void RegisterReplicatedProperties() override
    {
        ReplicatedProperties.push_back(&NetID);
    }

    uint64_t GetNetID() const override { return NetID; }
    float GetPriority() const override { return 1.0f; }

    bool HasAuthority() const override
    {
        // In a real client/server architecture, the client would need to know
        // its own connection to check for ownership. For this example,
        // we'll simulate this by having a flag.
        return bHasAuthority;
    }

    // Declare an RPC that requires authority
    DECLARE_RPC(Server_DoSomething);

    FRepProperty<uint64_t> NetID = 0;
    bool bHasAuthority = false; // By default, no authority
};

// Implement the RPC
IMPLEMENT_RPC(MyReplicatedObject, Server_DoSomething);


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
    std::cout << "--- GlobalReplication Ownership Test ---" << std::endl;

    // 1. Create a replicated object on the server
    MyReplicatedObject ServerObj(101);
    ServerObj.bHasAuthority = true; // Server has authority initially
    std::cout << "[Server] Created object " << ServerObj.GetNetID() << std::endl;

    // 2. Create and initialize the server driver
    ReplicationDriver Driver;
    Driver.RegisterObject(&ServerObj);

    Driver.OnNewConnection = [&](std::shared_ptr<IReplicationConnection> NewConn)
    {
        std::cout << "[Server] New connection established. Transferring ownership of object " << ServerObj.GetNetID() << std::endl;
        Driver.SetObjectOwner(&ServerObj, NewConn);

        // In a real implementation, the client would be notified of the ownership change.
        // For this test, we'll just assume the client now has authority.
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

    // 5. Wait a moment for the connection to be established and ownership transferred
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 6. Now, create a client-side representation of the object and call an RPC
    // that requires authority. Since ownership was transferred, this should execute locally.
    std::cout << "\n[Client] Attempting to call RPC with authority..." << std::endl;
    MyReplicatedObject ClientObj(101);
    ClientObj.bHasAuthority = true; // Simulate the client knowing it has authority
    ClientObj.Server_DoSomething();


    // 7. Stop the server
    bServerShouldStop = true;
    ServerThread.join();
    ClientThread.join();

    std::cout << "\n--- Test Complete ---" << std::endl;

    return 0;
}
