#include "structs.h"
#include "other.h"
#include "Net/UNetDriver.h"

class UEngine
{
    public: 
    
    //https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/UEngine/GetMaxTickRate
    static float GetMaxTickRate(float DeltaTime, bool bAllowFrameRateSmoothing) {
        float MaxTickRate = 0.f;
        if ( UNetDriver->GetNetMode() == NM_DedicatedServer )
        {
            MaxTickRate = 30.0f;
        }
        return MaxTickRate;
    }
}
