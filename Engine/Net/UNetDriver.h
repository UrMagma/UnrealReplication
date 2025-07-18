#include "Engine/structs.h"
#include "Engine/other.h"
#include "Engine/Net/UNetConnection.h"
#include "Engine/UEngine.h"

auto Engine = GetEngine();
class FNetworkNotify;

TArray<UNetConnection*> ClientConnections;



class UNetDriver
{
public:
    UObject* Actor;
    UObject* SubObj;
    UNetConnection* Connection;

	FString NetDriver; //temp?

    FString NetConnectionClass;
    FString ReplicationDriverClass;
    int NetServerMaxTickRate:1;
    int NetServerMaxTickRate;
    int MaxNetTickRate;
    UNetConnection* ServerConnection;

	enum ENetMode
	{
		NM_Standalone,
		NM_DedicatedServer,
		NM_ListenServer,
		NM_Client,
		NM_MAX,
	};

	ENetMode GetNetMode() {
		return ENetMode::NM_DedicatedServer;
	}
};

//https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Classes/Engine/NetDriver.h#L540
struct  FActorDestructionInfo
{
public:

	//TWeakObjectPtr<ULevel> Level; 
	TWeakObjectPtr<UObject> ObjOuter;
	FVector DestroyedPosition;
	//FNetworkGUID NetGUID;
	FString PathName;
	FName StreamingLevelName;
	//EChannelCloseReason Reason;

	/** When true the destruction info data will be sent even if the viewers are not close to the actor */
	bool bIgnoreDistanceCulling;
};

struct FActorPriority //https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Classes/Engine/NetDriver.h#L568
{
	int						Priority;	// Update priority, higher = more important.
	
	FNetworkObjectInfo*			ActorInfo;	// Actor info.
	class UActorChannel*		Channel;	// Actor channel.

	FActorDestructionInfo *	DestructionInfo;	// Destroy an actor

	FActorPriority() : 
		Priority(0), ActorInfo(NULL), Channel(NULL), DestructionInfo(NULL)
	{}

	FActorPriority(UNetConnection* InConnection, class UActorChannel* InChannel, FNetworkObjectInfo* InActorInfo, const TArray<struct FNetViewer>& Viewers, bool bLowBandwidth);
	FActorPriority(UNetConnection* InConnection, FActorDestructionInfo * DestructInfo, const TArray<struct FNetViewer>& Viewers );
};

/*FNetworkObjectList& GetNetworkObjectList()
{
	return *NetworkObjects;
}*/

UNetDriver* Driver;

UNetDriver* GetNetDriverName()
{
	return Driver;
}


class Replication : public Replication
{
	//not used on newer versions.
	bool InitListen(FNetworkNotify* InNotify, FURL& ListenUrl, bool breuseAddressAndPort, FString& Error);

	int ServerReplicateActors_PrepConnections(float DeltaSeconds)
	{

	}

	void ServerReplicateActors_BuildConsiderList(TArrary<FNetworkObjectInfo*> OutConsiderList,float ServerTickTime) /*@TODO FIX TMR*/
	{
		int NumInitDormant = 0;
		TArray<UObject*> ActorsToRemove; 

		for( TSharedPtr<FNetworkObjectInfo>& ObjectInfo : GetNetworkObjectList()) /*@TODO FIX TMR*/
		{
			FNetworkObjectInfo* ActorInfo = ObjectInfo.Get();
			if(!ActorInfo->bPendingNetUpdate && World->TimeSeconds <= ActorInfo->NextUpdateTime) /*@TODO FIX TMR*/
			{
				continue;
			}

			//if(ActorInfo->GetNetDriverName() !=NetDriverName); @TODO FIX TMR
		}
	}


	//https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Private/NetDriver.cpp#L4914
	int ServerReplicateActors(float DeltaSeconds)
	{
		int NumClientsToTick = ServerReplicateActors_PrepConnections( DeltaSeconds );


		int ServerTickTime = UEngine::GetMaxTickRate(DeltaSeconds, true); 
		if(ServerTickTime = 0.f)
		{
			ServerTickTime = DeltaSeconds;
		}
		else
		{
			ServerTickTime = 1.F/ServerTickTime;
		}

		TArray<FNetworkObjectInfo*> ConsiderList;
		
		ConsiderList.Num();

		ServerReplicateActors_BuildConsiderList(ConsiderList, ServerTickTime);

		TSet<UNetConnection*> ConnectionsToClose;

		if(i >= NumClientsToTick == 0) 
		{
			for(int ConsiderIdx = 0; ConsiderIdx < ConsiderList.Num(); ConsiderIdx++)
			{
				UObject* Actor = ConsiderList[ConsiderIdx]->Actor;

				//if(Actor != NULL  &&)
			}
		}
	}
};
