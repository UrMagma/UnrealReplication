#include "./Engine/structs.h"
#include "./Engine/other.h"
#include "./Engine/Net/UNetConnection.h"

auto Engine = GetEngine();

class UNetDriver
{
    public:

    Actor* Actor;
    UObject* SubObj;
    UNetConnection* Connection;

    public:
    FString NetConnectionClass;
    FString ReplicationDriverClass;
    int NetServerMaxTickRate:1;
    int NetServerMaxTickRate;
    int MaxNetTickRate;

    UNetConnection* ServerConnection;
    TArray<UNetConnection*> ClientConnections;


};

//https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Classes/Engine/NetDriver.h#L540
struct  FActorDestructionInfo
{
public:

	TWeakObjectPtr<ULevel> Level; 
	TWeakObjectPtr<UObject> ObjOuter;
	FVector DestroyedPosition;
	FNetworkGUID NetGUID;
	FString PathName;
	FName StreamingLevelName;
	//EChannelCloseReason Reason;

	/** When true the destruction info data will be sent even if the viewers are not close to the actor */
	bool bIgnoreDistanceCulling;


struct FActorPriority //https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Classes/Engine/NetDriver.h#L568
{
	int						Priority;	// Update priority, higher = more important.
	
	FNetworkObjectInfo*			ActorInfo;	// Actor info.
	class UActorChannel*		Channel;	// Actor channel.

	FActorDestructionInfo *	DestructionInfo;	// Destroy an actor

	FActorPriority() : 
		Priority(0), ActorInfo(NULL), Channel(NULL), DestructionInfo(NULL)
	{}

	FActorPriority(class UNetConnection* InConnection, class UActorChannel* InChannel, FNetworkObjectInfo* InActorInfo, const TArray<struct FNetViewer>& Viewers, bool bLowBandwidth);
	FActorPriority(class UNetConnection* InConnection, FActorDestructionInfo * DestructInfo, const TArray<struct FNetViewer>& Viewers );
};

//not used on newer versions.
bool InitListen(class FNetworkNotify* InNotify, FURL& ListenUrl, bool breuseAddressAndPort, FString& Error)
{

}

//https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Private/NetDriver.cpp#L5315
void AddClientConnection(UNetConnection* NewConnection)
{
 
}

void SetWorld(UNetDriver* Driver, UWorld* World)
{

}

int ServerReplicateActors_Prep()
{

}

void ServerReplicateActors_BuildConsiderList(TArrary<FNetworkObjectInfo*> OutConsiderList,float ServerTickTime)
{
    
}

int ServerReplicateActors(float DeltaSeconds)
{

}

