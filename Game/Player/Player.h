#include "../Engine/DataTables.h"
#include "../Engine/other.h"
#include "../Engine/structs.h"

UNetDriver
class APlayer : public APlayer //APlayerPawn_Athena_C
{
    void RecievePossessed(class AController** NewController);
    void RecieveBeginPlay();
    void RecieveDestroyed();
    void RecieveTick(float* deltaSeconds);

    Net
};