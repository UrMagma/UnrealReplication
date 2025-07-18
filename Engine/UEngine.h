#include "./Engine/structs.h"
#include "./Engine/other.h"

//https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Engine/UEngine/GetMaxTickRate
float GetMaxTickRate(float DeltaTime, bool bAllowFrameRateSmoothing) {
    return 30.f; // for now, this is basically the max tick rate that the server can run.
}
