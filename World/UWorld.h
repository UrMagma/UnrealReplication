#include "./Engine/structs.h"
#include "./Engine/other.h"
#include "Engine/Net/UNetDriver.h"

class UWorld
{
	//Alot more needs to be added to this...

	public:
	/**  Time in seconds since level began play, but IS paused when the game is paused, and IS dilated/clamped. */
	float TimeSeconds;
	/**  Time in seconds since level began play, but IS NOT paused when the game is paused, and IS dilated/clamped. */
	float UnpausedTimeSeconds;
	/** Time in seconds since level began play, but IS NOT paused when the game is paused, and IS NOT dilated/clamped. */
	float RealTimeSeconds;
	/** Time in seconds since level began play, but IS paused when the game is paused, and IS NOT dilated/clamped. */
	float AudioTimeSeconds;
	/** Frame delta time in seconds adjusted by e.g. time dilation. */
	float DeltaTimeSeconds;
	/** time at which to start pause **/
	float PauseDelay;

	void SetNetDriver(UNetDriver* INetDriver) { UNetDriver.NetDriver = INetDriver;} //this might work not 100% sure tho
};


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
