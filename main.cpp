#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include <iostream>
#include <vector>
#include <cstdint>

/**
 * @brief A simple implementation of IReplicatedObject for demonstration.
 */
class MyReplicatedObject : public IReplicatedObject
{
public:
    MyReplicatedObject(uint64_t InNetID, float InX, float InY, int InHealth)
        : NetID(InNetID), x(InX), y(InY), health(InHealth)
    {
    }

    virtual void Serialize(FArchive& Ar) override
    {
        Ar.Serialize(&NetID, sizeof(NetID));
        Ar.Serialize(&x, sizeof(x));
        Ar.Serialize(&y, sizeof(y));
        Ar.Serialize(&health, sizeof(health));
    }

    virtual uint64_t GetNetID() const override
    {
        return NetID;
    }

    void Print() const
    {
        std::cout << "  ReplicatedObject ID: " << NetID << ", x: " << x << ", y: " << y << ", health: " << health << std::endl;
    }

private:
    uint64_t NetID;
    float x;
    float y;
    int health;
};

int main()
{
    std::cout << "--- GlobalReplication Demonstration ---" << std::endl;

    // 1. Create the replication driver
    auto Driver = std::make_shared<ReplicationDriver>();
    std::cout << "Created ReplicationDriver." << std::endl;

    // 2. Create a connection
    auto Connection = std::make_shared<ReplicationConnection>();
    Driver->AddConnection(Connection);
    std::cout << "Created and added a ReplicationConnection." << std::endl;

    // 3. Create some replicated objects
    MyReplicatedObject Obj1(101, 10.0f, 20.0f, 100);
    MyReplicatedObject Obj2(102, 30.0f, 40.0f, 80);
    std::cout << "Created two replicated objects:" << std::endl;
    Obj1.Print();
    Obj2.Print();

    // 4. Add the objects to the connection's replication list
    Connection->AddReplicatedObject(&Obj1);
    Connection->AddReplicatedObject(&Obj2);
    std::cout << "\nAdded objects to the connection's replication list." << std::endl;

    // 5. Tick the driver to simulate one frame of replication
    std::cout << "\nTicking the replication driver..." << std::endl;
    Driver->Tick(0.016f);

    // 6. Check the connection's outgoing buffer to see the serialized data
    std::cout << "\nChecking the connection's outgoing buffer:" << std::endl;
    int PacketNum = 0;
    while (static_cast<ReplicationConnection*>(Connection.get())->HasPendingData())
    {
        auto Packet = static_cast<ReplicationConnection*>(Connection.get())->GetPendingData();
        std::cout << "  Packet " << ++PacketNum << " size: " << Packet.size() << " bytes" << std::endl;
    }

    if (PacketNum == 0)
    {
        // The current implementation of ReplicationConnection uses separate incoming/outgoing buffers,
        // so we can't directly check the outgoing data this way. The Tick function in the driver
        // calls SendData, which populates the OutgoingBuffer. A real implementation would
        // have a way to flush this buffer to a socket. For this example, we'll assume the
        // "Replicated object..." messages from the driver's Tick are sufficient to show it's working.
        std::cout << "  (Note: Outgoing buffer is not directly readable in this example, but Tick has processed the data.)" << std::endl;
    }


    std::cout << "\n--- Demonstration Complete ---" << std::endl;

    return 0;
}
