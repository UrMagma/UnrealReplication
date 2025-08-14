#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/RPC.h"

void IReplicatedObject::RegisterBuiltInRPCs()
{
    static bool bRPCsRegistered = false;
    if (bRPCsRegistered)
    {
        return;
    }
    bRPCsRegistered = true;

    REGISTER_RPC(IReplicatedObject, Server_RequestOwnership);
    REGISTER_RPC(IReplicatedObject, Client_GainedOwnership);
    REGISTER_RPC(IReplicatedObject, Client_LostOwnership);
}

// The Server_RequestOwnership RPC is handled entirely by the ReplicationDriver.
// This function exists so it can be registered as a valid RPC target.
void IReplicatedObject::Server_RequestOwnership()
{
    // Empty implementation.
}

// Called on a client when it gains network ownership of this object.
void IReplicatedObject::Client_GainedOwnership()
{
    // Base implementation does nothing. Derived classes can override this.
}

#include "GlobalReplication/Public/ReplicatedComponent.h"

void IReplicatedObject::AddComponent(UReplicatedComponent* Comp)
{
    if (Comp)
    {
        Comp->SetSubObjectIndex(SubObjects.size());
        SubObjects.push_back(Comp);
    }
}

// Called on a client when it loses network ownership of this object.
void IReplicatedObject::Client_LostOwnership()
{
    // Base implementation does nothing. Derived classes can override this.
}
