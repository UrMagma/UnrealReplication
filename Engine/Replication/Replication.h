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

int ServerReplicateActors(float DeltaSeconds)
{
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
    }
        
    //client shouldnt be ticked this frame.
    if(i >= NumClientsToTick)
    {
        for(int32_t ConsiderIDx = 0; ConsiderIDx < ConsideerList.Num(); ConsiderIDx++)
        {
            class AActor* Actor = ConsiderList[ConsiderIDx]->Actor;
        }
    }
}

