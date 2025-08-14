#pragma once

#include "GlobalReplication.h"

class UReplicatedComponent : public IReplicatedObject
{
public:
    UReplicatedComponent(IReplicatedObject* InOwner) : Owner(InOwner) {}
    virtual ~UReplicatedComponent() = default;

    IReplicatedObject* GetOwner() const { return Owner; }

private:
    IReplicatedObject* Owner;
};
