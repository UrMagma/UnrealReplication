#pragma once

#include "GlobalReplication.h"

class UReplicatedComponent : public FReplicatedObjectBase
{
public:
    UReplicatedComponent(IReplicatedObject* InOwner);
    virtual ~UReplicatedComponent() = default;

    IReplicatedObject* GetOwner() const { return Owner; }
    uint8_t GetSubObjectIndex() const { return SubObjectIndex; }
    void SetSubObjectIndex(uint8_t Index) { SubObjectIndex = Index; }

protected:
    // Components must implement this to register their own properties.
    virtual void RegisterReplicatedProperties() override = 0;

private:
    IReplicatedObject* Owner;
    uint8_t SubObjectIndex;
};
