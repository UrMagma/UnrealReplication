#include "./Engine/structs.h"
#include "./Engine/other.h"

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
