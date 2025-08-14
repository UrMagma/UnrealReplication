#pragma once

#include "GlobalReplication.h"
#include <vector>
#include <memory>

class ReplicationDriver : public IReplicationDriver
{
public:
    ReplicationDriver();
    virtual ~ReplicationDriver() = default;

    virtual void AddConnection(std::shared_ptr<IReplicationConnection> Conn) override;
    virtual void RemoveConnection(std::shared_ptr<IReplicationConnection> Conn) override;
    virtual void Tick(float DeltaTime) override;

private:
    std::vector<std::shared_ptr<IReplicationConnection>> Connections;
};
