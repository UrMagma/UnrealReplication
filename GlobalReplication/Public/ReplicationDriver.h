#pragma once

#include "GlobalReplication.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include "Socket.h"

// Custom hash and equality for sockaddr_in to use it as a key in unordered_map
namespace std {
    template <>
    struct hash<sockaddr_in> {
        size_t operator()(const sockaddr_in& addr) const {
            return hash<uint32_t>()(addr.sin_addr.s_addr) ^ hash<uint16_t>()(addr.sin_port);
        }
    };

    template <>
    struct equal_to<sockaddr_in> {
        bool operator()(const sockaddr_in& a, const sockaddr_in& b) const {
            return a.sin_addr.s_addr == b.sin_addr.s_addr && a.sin_port == b.sin_port;
        }
    };
}

class ReplicationDriver : public IReplicationDriver
{
public:
    ReplicationDriver();
    virtual ~ReplicationDriver() = default;

    bool Init(uint16_t Port);
    virtual void Tick(float DeltaTime) override;

    // Callback for when a new connection is established
    std::function<void(std::shared_ptr<IReplicationConnection>)> OnNewConnection;

    // These are now public to allow the example to add objects to connections
    virtual void AddConnection(std::shared_ptr<IReplicationConnection> Conn) override;
    virtual void RemoveConnection(std::shared_ptr<IReplicationConnection> Conn) override;
    void RegisterObject(IReplicatedObject* Obj);
    void SetObjectOwner(IReplicatedObject* Obj, std::shared_ptr<IReplicationConnection> NewOwner);

protected:
    void HandleRPC(const std::vector<uint8_t>& RPCData, std::shared_ptr<IReplicationConnection> SourceConnection);
    void HandlePropertyUpdate(const std::vector<uint8_t>& PacketData);

    FSocket ListenSocket;
    std::unordered_map<sockaddr_in, std::shared_ptr<IReplicationConnection>> Connections;
    std::unordered_map<uint64_t, IReplicatedObject*> NetIDToObjectMap;
};
