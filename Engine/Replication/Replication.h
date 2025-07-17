#include "Engine/structs.h"
#include "Engine/other.h"
/*THIS IS VERY SHIT AND WILL HAVE TO BE REDONE*/
class UNetConnection;

UObject* NetDriver;

UObject GEngine = GetEngine();

/*https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Private/NetDriver.cpp#L5315*/
void AddClientConnection(UNetConnection* NewConnection)
{
    /*Will have to finish this shit*/
    auto ConnAddr = NewConnection;

    if(ConnAddr.IsValid())
    {
        
    }
}

int ServerReplicateActors_Prep(const float DeltaSeconds)
{
    int32_t NumClientsToTick = ClientConnections.Num();
}

https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Private/NetDriver.cpp#L4938
int ServerReplicateActors(float DeltaSeconds)
{
    /*Im going to upload this even tho not much has changed but this will be switched to using Connection->ViewTarget, should already be using it
    but life isnt perfect.
    */


    //Replication Frame (Milxnor)
    if (Engine_Version == 416)
        ++* (int32_t*)(NetDriver + 0x288);
    if (Engine_Version == 419)
        ++*(int32_t*)(NetDriver + 0x2C8);
    if (Engine_Version == 420)
        ++* (int32_t*)(NetDriver + 0x330);
    if (Engine_Version == 424)
        ++*(int32_t*)(NetDriver + 0x410);

    static auto ClientConnectionsOffset = GetOffset(NetDriver, "ClientConnections");    
    static auto ClientConnections = (TArray<UObject*>*)(__int64(NetDriver) + ClientConnectionsOffset);

    int32_t NumClientsToTick = ServerReplicateActors_Prep(DeltaSeconds);

    if(NumClientsToTick = 0)
    {
       return 0;
    }
     
    for(int32_t i=0; i < ClientConnections.Num(); i++)
    {
        UNetConnection* Connection = ClientConnections[i];

        if(FUNC_NetValidate = 2)
        {

        }
    }
        
    //(HONESTLY JUST NEED TO USE VIEWTARGET FOR THE WHOLE THING)
    if(i >= NumClientsToTick)
    {
        for(int32_t ConsiderIDx = 0; ConsiderIDx < ConsideerList.Num(); ConsiderIDx++)
        {
            class AActor* Actor = ConsiderList[ConsiderIDx]->Actor;

            if(Actor != NULL && !ConsiderList[ConsiderIDx] -> bPendingNetUpdate)
            {
                UActorChannel* Channel = UNetConnection->FindActorChannelRef(ConsiderList[ConsiderIDx]->WeakActor);

                if(Channel != NULL && Channel->LastUpdateTime < ConsiderList[ConsiderIDx]->LastNetUpdateTimeStamp)
                {
                    ConsiderList[ConsiderIDx->bPendingNetUpdate]->bPendingNetUpdate = true;
                }
            }
        }
        Connection->TimeSensitive = false;
    }

    //Integrate ViewTarget, more portable maybe? and just the right way.
   // https://github.com/EpicGames/UnrealEngine/blob/3abfe77d0b24a6d8bacebd27766912e5a5fa6f02/Engine/Source/Runtime/Engine/Private/NetDriver.cpp#L5315
}

