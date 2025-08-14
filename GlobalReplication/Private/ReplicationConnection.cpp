#include "GlobalReplication/Public/ReplicationConnection.h"
#include <algorithm>

ReplicationConnection::ReplicationConnection()
{
}

void ReplicationConnection::SendData(const std::vector<uint8_t>& Data)
{
    OutgoingBuffer.push(Data);
}

bool ReplicationConnection::HasPendingData() const
{
    return !IncomingBuffer.empty();
}

std::vector<uint8_t> ReplicationConnection::GetPendingData()
{
    if (IncomingBuffer.empty())
    {
        return {};
    }

    std::vector<uint8_t> Data = IncomingBuffer.front();
    IncomingBuffer.pop();
    return Data;
}

void ReplicationConnection::AddReplicatedObject(IReplicatedObject* Obj)
{
    ReplicatedObjects.push_back(Obj);
}

void ReplicationConnection::RemoveReplicatedObject(IReplicatedObject* Obj)
{
    ReplicatedObjects.erase(std::remove(ReplicatedObjects.begin(), ReplicatedObjects.end(), Obj), ReplicatedObjects.end());
}
