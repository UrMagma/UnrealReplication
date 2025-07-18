#include "Engine/structs.h"
#include "Engine/Net/enum.h"
#include "Engine/other.h"
//https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Classes/Engine/NetConnection.h#L39
class UNetConnection
{
	public:
	
    class UActorChannel;

    TArray<class UChildConnection*> Children;

    class UNetDriver* Driver;

    TArray<class UChannel*> OpenChannels;

    UObject* ViewTarget;

    UObject* OwningActor;

    double			LastReceiveTime;		// Last time a packet was received, for timeout checking.
	double			LastReceiveRealtime;	// Last time a packet was received, using real time seconds (FPlatformTime::Seconds)
	double			LastGoodPacketRealtime;	// Last real time a packet was considered valid
	double			LastSendTime;			// Last time a packet was sent, for keepalives.
	double			LastTickTime;			// Last time of polling.
	int			QueuedBits;			// Bits assumed to be queued up.
	int			TickCount;				// Count of ticks.
	uint			LastProcessedFrame;   // The last frame where we gathered and processed actors for this connection
};

enum Type
{
	Invalid		= 0,		// This must be a client (which doesn't use this state) or uninitialized.
	LoggingIn	= 1,		// The client is currently logging in.
	Welcomed	= 2,		// Told client to load map and will respond with SendJoin
	ReceivedJoin = 3,		// NMT_Join received and a player controller has been created
	CleanedUp	= 4			// Cleanup has been called at least once, the connection is considered abandoned/terminated/gone
};

enum EConnectionState
{
	USOCK_Invalid   = 0, // Connection is invalid, possibly uninitialized.
	USOCK_Closed    = 1, // Connection permanently closed.
	USOCK_Pending	= 2, // Connection is awaiting connection.
	USOCK_Open      = 3, // Connection is open.
};