#include "Engine/Net/UNetConnection.h"
#include "Engine/Net/UNetDriver.h"

class AActor;
class FArchive;

class FNetworkObjectKeyFuncs
{

};

struct FNetworkObjectInfo
{
    /** Pointer to the replicated actor. */
	AActor* Actor;

	/** WeakPtr to actor. This is cached here to prevent constantly constructing one when needed for (things like) keys in TMaps/TSets */
	TWeakObjectPtr<AActor> WeakActor;

	/** Next time to consider replicating the actor. Based on FPlatformTime::Seconds(). */
	double NextUpdateTime;

	/** Last absolute time in seconds since actor actually sent something during replication */
	double LastNetReplicateTime;

	/** Optimal delta between replication updates based on how frequently actor properties are actually changing */
	float OptimalNetUpdateDelta;

	/*float LastNetUpdateTime; deprecated*/
	double LastNetUpdateTimestamp;

	/** List of connections that this actor is dormant on */
	TSet<TWeakObjectPtr<UNetConnection>> DormantConnections;

	/** A list of connections that this actor has recently been dormant on, but the actor doesn't have a channel open yet.
	*  These need to be differentiated from actors that the client doesn't know about, but there's no explicit list for just those actors.
	*  (this list will be very transient, with connections being moved off the DormantConnections list, onto this list, and then off once the actor has a channel again)
	*/
	TSet<TWeakObjectPtr<UNetConnection>> RecentlyDormantConnections;

	/** Is this object still pending a full net update due to clients that weren't able to replicate the actor at the time of LastNetUpdateTime */
	int bPendingNetUpdate : 1;

    UNetDriver* NetDrive;

    UNetDriver* GetNetDriverName()
    {
        return NetDrive;
    }
};

/*class FNetworkObjectList : public FNetworkObjectList
{
    TSet<TSharedPtr<FNetworkObjectInfo>, FNetworkObjectKeyFuncs> FNetworkObjectSet;

    TSharedPtr<FNetworkObjectInfo> Find(AActor* Actor)
    {
        if(Actor == nullptr)
        {
            //return nullptr
        }

        if(TSharedPtr<FNetworkObjectInfo>* InfoPtr = FNetworkObjectList::Find(Actor))
        {

        }
    }

};*/