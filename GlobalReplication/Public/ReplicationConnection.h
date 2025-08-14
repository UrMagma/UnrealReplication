#pragma once

#include "GlobalReplication.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include "Socket.h" // For sockaddr_in

class ReplicationConnection : public IReplicationConnection, public std::enable_shared_from_this<ReplicationConnection>
{
public:
    ReplicationConnection(const sockaddr_in& InAddr);
    virtual ~ReplicationConnection() = default;

    virtual void SendData(FSocket& Socket, const std::vector<uint8_t>& Data) override;
    virtual void SendRPC(const std::vector<uint8_t>& RPCData) override;

    virtual void AddReplicatedObject(IReplicatedObject* Obj) override;
    virtual void RemoveReplicatedObject(IReplicatedObject* Obj) override;

    const std::unordered_map<uint64_t, IReplicatedObject*>& GetReplicatedObjects() const { return ReplicatedObjects; }
    const sockaddr_in& GetAddress() const { return Address; }

    // This is a temporary way to get the outgoing RPC buffer for the example
    std::queue<std::vector<uint8_t>>& GetOutgoingRPCBuffer() { return OutgoingRPCBuffer; }

private:
    std::unordered_map<uint64_t, IReplicatedObject*> ReplicatedObjects;
    sockaddr_in Address;
    std::queue<std::vector<uint8_t>> OutgoingRPCBuffer;
};
