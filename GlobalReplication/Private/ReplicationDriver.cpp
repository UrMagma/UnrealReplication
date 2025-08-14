#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/MemoryArchive.h"
#include <iostream>
#include <algorithm>

ReplicationDriver::ReplicationDriver()
{
}

void ReplicationDriver::AddConnection(std::shared_ptr<IReplicationConnection> Conn)
{
    Connections.push_back(Conn);
}

void ReplicationDriver::RemoveConnection(std::shared_ptr<IReplicationConnection> Conn)
{
    Connections.erase(std::remove(Connections.begin(), Connections.end(), Conn), Connections.end());
}

void ReplicationDriver::Tick(float DeltaTime)
{
    // For each connection...
    for (auto& Conn : Connections)
    {
        // ...get the list of objects to replicate...
        auto& ReplicatedObjects = static_cast<ReplicationConnection*>(Conn.get())->GetReplicatedObjects();

        // ...and for each object...
        for (auto& Obj : ReplicatedObjects)
        {
            // ...serialize its state into a buffer...
            std::vector<uint8_t> Buffer;
            FMemoryArchive Ar(Buffer);
            Obj->Serialize(Ar);

            // ...and send it over the connection.
            Conn->SendData(Buffer);

            std::cout << "Replicated object " << Obj->GetNetID() << " to connection." << std::endl;
        }
    }
}
