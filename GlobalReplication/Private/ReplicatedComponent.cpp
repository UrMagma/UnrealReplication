#include "GlobalReplication/Public/ReplicatedComponent.h"

UReplicatedComponent::UReplicatedComponent(IReplicatedObject* InOwner)
    : Owner(InOwner), SubObjectIndex(0)
{
    // NOTE: The most-derived class is responsible for calling RegisterReplicatedProperties()
    // in its own constructor. It is a pure virtual function and cannot be called here.
}
