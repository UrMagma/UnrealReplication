#pragma once

#include "GlobalReplication.h"
#include <vector>
#include <queue>

class ReplicationConnection : public IReplicationConnection, public std::enable_shared_from_this<ReplicationConnection>
{
public:
    ReplicationConnection();
    virtual ~ReplicationConnection() = default;

    virtual void SendData(const std::vector<uint8_t>& Data) override;
    virtual bool HasPendingData() const override;
    virtual std::vector<uint8_t> GetPendingData() override;

    virtual void AddReplicatedObject(IReplicatedObject* Obj) override;
    virtual void RemoveReplicatedObject(IReplicatedObject* Obj) override;

    const std::vector<IReplicatedObject*>& GetReplicatedObjects() const { return ReplicatedObjects; }

private:
    std::vector<IReplicatedObject*> ReplicatedObjects;
    std::queue<std::vector<uint8_t>> IncomingBuffer;
    std::queue<std::vector<uint8_t>> OutgoingBuffer;
};
