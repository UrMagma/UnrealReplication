#include "Engine/structs.h"
#include "Engine/other.h"
#include "Engine/Net/UNetConnection.h"
#include "Engine/UEngine.h"
#include "Engine/World/UWorld.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Engine/Net/ActorChannel.h"
#include "Engine/PlayerController.h"

class FNetworkNotify;
UWorld* World;

class UNetDriver
{
public:
    FString NetConnectionClass;
    FString NetDriver;
    FString ReplicationDriverClass;
    int NetServerMaxTickRate;
    int MaxNetTickRate;
    TArray<UNetConnection*> ClientConnections;
    UNetConnection* ServerConnection;
    TArray<FActorDestructionInfo> RecentlyDestroyedActors; // Track recently destroyed actors for replication



    // Socket handle, etc, would go here.
    FSocket* ListenSocket;

    UNetDriver()
        : NetServerMaxTickRate(30), MaxNetTickRate(60), ServerConnection(nullptr), ListenSocket(7777)
    {}

    /** Initialize as a listen server: bind socket, listen for clients, setup network state */
    bool InitListen(FNetworkNotify* InNotify, FURL& ListenUrl, bool bReuseAddressAndPort, FString& Error)
    {
        ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (!SocketSubsystem)
        {
            Error = TEXT("Failed to get socket subsystem");
            return false;
        }

        // Create a TCP socket for listening
        ListenSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("UNetDriver Listen Socket"), false);
        if (!ListenSocket)
        {
            Error = TEXT("Failed to create listen socket");
            return false;
        }

        // Setup address to bind
        TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
        bool bIsValid;
        Addr->SetIp(*ListenUrl.Host, bIsValid);
        Addr->SetPort(ListenUrl.Port);
        if (!bIsValid)
        {
            Error = TEXT("Invalid IP address");
            SocketSubsystem->DestroySocket(ListenSocket);
            ListenSocket = nullptr;
            return false;
        }

        if (bReuseAddressAndPort)
        {
            ListenSocket->SetReuseAddr(true);
            ListenSocket->SetReusePort(true);
        }

        // Bind socket
        if (!ListenSocket->Bind(*Addr))
        {
            Error = TEXT("Failed to bind listen socket");
            SocketSubsystem->DestroySocket(ListenSocket);
            ListenSocket = nullptr;
            return false;
        }

        // Set non-blocking
        ListenSocket->SetNonBlocking(true);

        // Start listening
        if (!ListenSocket->Listen(8)) // backlog of 8 connections
        {
            Error = TEXT("Failed to listen on socket");
            SocketSubsystem->DestroySocket(ListenSocket);
            ListenSocket = nullptr;
            return false;
        }

        return true;
    }

    /** Accept new connections if any*/
    void TickDispatch(float DeltaSeconds)
    {
        if (!ListenSocket)
            return;

        bool bHasPendingConnection = false;
        while (ListenSocket->HasPendingConnection(bHasPendingConnection) && bHasPendingConnection)
        {
            // Accept incoming connection
            FSocket* NewSocket = ListenSocket->Accept(TEXT("Incoming Connection"));
            if (NewSocket)
            {
                // Create a new NetConnection for this socket
                UNetConnection* NewConnection = new UNetConnection();
                NewConnection->InitConnection(NewSocket);
                ClientConnections.Add(NewConnection);
            }
            else
            {
                // No socket accepted, break out
                break;
            }
        }
    }

    /** Prepare connections for replication tick: reset per-tick state, validate open connections */
    void PrepareConnections()
    {
        for (int32 i = ClientConnections.Num() - 1; i >= 0; --i)
        {
            UNetConnection* Conn = ClientConnections[i];
            if (!Conn || Conn->State == USOCK_Closed)
            {
                ClientConnections.RemoveAt(i);
                continue;
            }
            Conn->ResetReplicationState();
        }
    }

    /** Build the list of networked actors to consider for replication this tick */
    void BuildConsiderList(TArray<FNetworkObjectInfo*>& OutConsiderList, float ServerTickTime)
    {
        for (TSharedPtr<FNetworkObjectInfo> ObjectInfo : GetNetworkObjectList())
        {
            FNetworkObjectInfo* ActorInfo = ObjectInfo.Get();
            if (!ActorInfo || !ActorInfo->Actor)
                continue;
            // Only replicate if pending net update or needs scheduled update
            if (!ActorInfo->bPendingNetUpdate && World->TimeSeconds <= ActorInfo->NextUpdateTime)
                continue;
            // Filter out dormant, irrelevant, torn-off actors
            if (ActorInfo->bIsDormant || ActorInfo->bTornOff)
                continue;
            OutConsiderList.Add(ActorInfo);
        }
    }

    /** Calculate priority for each actor and sort for replication */
    void PrioritizeActors(const TArray<FNetworkObjectInfo*>& ConsiderList, TArray<FActorPriority>& OutPrioritizedList, const TArray<FNetViewer>& Viewers)
    {
        for (FNetworkObjectInfo* ActorInfo : ConsiderList)
        {
            // Find or create actor channel for each connection as needed
            UActorChannel* Channel = FindOrCreateActorChannel(ActorInfo->Actor);
            // Calculate priority (distance, relevance, etc.)
            int Priority = CalculateActorPriority(ActorInfo, Channel, Viewers);
            OutPrioritizedList.Add(FActorPriority(Priority, ActorInfo, Channel, nullptr));
        }
        // Sort descending by priority (highest = most important)
        OutPrioritizedList.Sort([](const FActorPriority& A, const FActorPriority& B) { return A.Priority > B.Priority; });
    }

    /** Replicate all relevant actors to all connections */
    void ServerReplicateActors(float DeltaSeconds)
    {
        PrepareConnections();

        float ServerTickTime = UEngine::GetMaxTickRate(DeltaSeconds, true);
        if (ServerTickTime == 0.f)
        {
            ServerTickTime = DeltaSeconds;
        }
        else
        {
            ServerTickTime = 1.f / ServerTickTime;
        }

        TArray<FNetworkObjectInfo*> ConsiderList;
        BuildConsiderList(ConsiderList, ServerTickTime);

        TArray<FNetViewer> Viewers;
        // Build Viewers array from all player controllers, etc.
        BuildNetViewers(Viewers);

        TArray<FActorPriority> PrioritizedList;
        PrioritizeActors(ConsiderList, PrioritizedList, Viewers);

        // Replicate prioritized actors to each connection
        for (UNetConnection* Connection : ClientConnections)
        {
            if (!Connection || Connection->State == USOCK_Closed)
                continue;
            for (const FActorPriority& ActorPri : PrioritizedList)
            {
                ReplicateToConnection(Connection, ActorPri.ActorInfo, ActorPri.Channel);
            }
        }

        // Replicate destruction events
        ProcessDestruction();

        // Enforce per-connection bandwidth limits
        EnforceBandwidthLimits();
    }

    /** Replicate a single actor to a connection, using its actor channel */
    void ReplicateToConnection(UNetConnection* Connection, FNetworkObjectInfo* ActorInfo, UActorChannel* Channel)
    {
        if (!Connection || !ActorInfo || !ActorInfo->Actor)
            return;
        if (!Channel)
        {
            Channel = CreateActorChannel(Connection, ActorInfo->Actor);
            if (!Channel)
                return;
        }
        // Serialize changed properties of ActorInfo->Actor
        FOutBunch Bunch;
        SerializeActorProperties(ActorInfo->Actor, Bunch);
        // Send reliably or unreliably depending on actor/channel state
        if (Channel->IsReliable())
        {
            Channel->SendReliable(Bunch);
        }
        else
        {
            Channel->SendUnreliable(Bunch);
        }
    }

    /** Track and replicate destruction of actors */
    void ProcessDestruction()
    {
        for (const FActorDestructionInfo& Destruction : RecentlyDestroyedActors)
        {
            for (UNetConnection* Connection : ClientConnections)
            {
                if (!Connection)
                    continue;
                // Notify connection about actor destruction
                Connection->NotifyActorDestroyed(Destruction);
            }
        }
        // Clear after replicating
        RecentlyDestroyedActors.Empty();
    }

    /** Monitor and enforce bandwidth limits per connection */
    void EnforceBandwidthLimits()
    {
        for (UNetConnection* Connection : ClientConnections)
        {
            if (!Connection)
                continue;
            // Check bytes sent this tick and throttle if over limit
            if (Connection->BytesSentThisTick > Connection->MaxAllowedBytes)
            {
                Connection->Throttle();
            }
        }
    }

    // --- Helper and stub functions ---

    TArray<TSharedPtr<FNetworkObjectInfo>>& GetNetworkObjectList()
    {
        // Return reference to global or driver-owned networked object list
        static TArray<TSharedPtr<FNetworkObjectInfo>> Dummy;
        return Dummy;
    }

    void BuildNetViewers(TArray<FNetViewer>& OutViewers)
    {
        if (!World)
            return;

        for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
        {
            APlayerController* PC = Iterator->Get();
            if (PC && PC->GetPawn())
            {
                FNetViewer Viewer;
                Viewer.Viewer = PC;
                Viewer.ViewLocation = PC->GetPawn()->GetActorLocation();
                Viewer.ViewRotation = PC->GetPawn()->GetActorRotation();
                OutViewers.Add(Viewer);
            }
        }
    }

    UActorChannel* FindOrCreateActorChannel(UObject* Actor)
    {
        if (!Actor)
            return nullptr;

        // Check existing connections for an actor channel for this actor
        for (UNetConnection* Connection : ClientConnections)
        {
            if (!Connection)
                continue;
            for (UActorChannel* Channel : Connection->ActorChannels)
            {
                if (Channel && Channel->GetActor() == Actor)
                {
                    return Channel;
                }
            }
        }

        // Not found, create a new one for the first connection as an example
        if (ClientConnections.Num() > 0)
        {
            return CreateActorChannel(ClientConnections[0], Actor);
        }

        return nullptr;
    }

    UActorChannel* CreateActorChannel(UNetConnection* Connection, UObject* Actor)
    {
        if (!Connection || !Actor)
            return nullptr;

        UActorChannel* NewChannel = new UActorChannel(Connection);
        if (!NewChannel->Init(Actor))
        {
            delete NewChannel;
            return nullptr;
        }

        Connection->ActorChannels.Add(NewChannel);
        return NewChannel;
    }

    int CalculateActorPriority(FNetworkObjectInfo* ActorInfo, UActorChannel* Channel, const TArray<FNetViewer>& Viewers)
    {
        if (!ActorInfo || !ActorInfo->Actor)
            return 0;

        FVector ActorLocation = ActorInfo->Actor->GetActorLocation();
        float MinDistanceSq = FLT_MAX;

        for (const FNetViewer& Viewer : Viewers)
        {
            float DistSq = FVector::DistSquared(ActorLocation, Viewer.ViewLocation);
            if (DistSq < MinDistanceSq)
            {
                MinDistanceSq = DistSq;
            }
        }

        // Priority inversely proportional to distance, clamped to some range
        float Distance = FMath::Sqrt(MinDistanceSq);
        int Priority = FMath::Clamp<int>(10000 - static_cast<int>(Distance * 100), 0, 10000);

        // Increase priority if actor has pending net update
        if (ActorInfo->bPendingNetUpdate)
        {
            Priority += 5000;
        }

        return Priority;
    }

    void SerializeActorProperties(UObject* Actor, FOutBunch& Bunch)
    {
        if (!Actor)
            return;

        // Example: serialize a few properties by name (assuming reflection)
        for (TFieldIterator<FProperty> It(Actor->GetClass()); It; ++It)
        {
            FProperty* Property = *It;
            if (!Property)
                continue;

            // Only serialize replicated properties
            if (Property->HasAnyPropertyFlags(CPF_Net))
            {
                Property->SerializeItem(Bunch, Property->ContainerPtrToValuePtr<void>(Actor));
            }
        }
    }
};
