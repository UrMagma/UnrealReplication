#include "Engine/structs.h"
#include "Engine/Net/enum.h"

class UNetConnection : public UPlayer
{
    TArray<class UChildConnection*> Children;

    class UNetDriver* Driver;

    TArray<class UChannel*> OpenChannels;

    Actor* ViewTarget;

    Actor* OwningActor;

    int32_t	TickCount;		
};