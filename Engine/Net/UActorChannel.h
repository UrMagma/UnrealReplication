#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map> // For TMap in FObjectReplicator
#include <set> // For TSet in UActorChannel

#include "other.h"
#include "structs.h"
#include "UNetConnection.h" // UNetConnection is needed for OwningConnection

// Forward declarations for types used within UActorChannel
class UActorComponent;
class AActor;
class FInBunch;
class FOutBunch;
class FObjectReplicator; // Defined below
class FNetBitWriter;     // Defined below
class FNetBitReader;     // Defined below

// --- Simplified Internal Types for UActorChannel ---

// Simplified FNetworkGUID (from NetConnection.h)
struct FNetworkGUID
{
    uint32 Value;
    FNetworkGUID() : Value(0) {}
    FNetworkGUID(uint32 InValue) : Value(InValue) {}
    bool IsValid() const { return Value != 0; }
    bool operator<(const FNetworkGUID& Other) const { return Value < Other.Value; }
    bool operator==(const FNetworkGUID& Other) const { return Value == Other.Value; }
};

// Simplified FReplicationFlags (from ActorChannel.h)
struct FReplicationFlags
{
    bool bNetInitial = false;
    bool bUseCustomSubobjectReplication = false;
};

// Simplified FObjectReplicator (from ActorChannel.h)
class FObjectReplicator
{
public:
    // This class would manage the actual property and RPC replication logic for an object.
    void ReplicateProperties(FOutBunch& Bunch, const FReplicationFlags& RepFlags)
    {
        // Conceptual: Serialize properties into the bunch
        // std::cout << "  FObjectReplicator: Replicating properties.\n";
    }
};

// Simplified FNetBitWriter (from ActorChannel.h) - inherits from FOutBunch
class FNetBitWriter : public FOutBunch
{
public:
    // Inherits WriteBytes from FOutBunch.
    // In Unreal, this would handle bit-level writing.
};

// Simplified FNetBitReader (from ActorChannel.h)
class FNetBitReader
{
public:
    std::vector<uint8_t> Data;
    int32 ReadPos = 0;
    void ReadBytes(void* OutData, int32 Count) {
        if (ReadPos + Count <= Data.size()) {
            memcpy(OutData, Data.data() + ReadPos, Count);
            ReadPos += Count;
        }
    }
};

// Simplified FInBunch (from ActorChannel.h)
class FInBunch
{
public:
    std::vector<uint8_t> Data;
    int32 ReadPos = 0;
    // Add methods for reading data
};

// Simplified FQueuedBunchObjectReference (from ActorChannel.h)
struct FQueuedBunchObjectReference {};

// Simplified ESetChannelActorFlags (from ActorChannel.h)
enum class ESetChannelActorFlags : uint32
{
	None					= 0,
	SkipReplicatorCreation	= (1 << 0),
	SkipMarkActive			= (1 << 1),
};

// Simplified EChannelCloseReason (from Channel.h) - only essential reasons
enum EChannelCloseReason
{
    CHAN_CloseReason_Error,
    CHAN_CloseReason_Destroyed,
    CHAN_CloseReason_TearOff,
    CHAN_CloseReason_Dormancy,
    CHAN_CloseReason_ClientDisconnect,
    CHAN_CloseReason_ServerTravel,
    CHAN_CloseReason_ActorIrrelevant,
    CHAN_CloseReason_MAX // Sentinel for max value
};

/**
 * @brief A channel for exchanging actor and its subobject's properties and RPCs.
 * Mimicking Unreal Engine's UActorChannel.
 * This simplified version focuses on core functionality for demonstration.
 */
class UActorChannel : public UObject
{
public:
    // --- Public Variables ---
    UObject* Actor;                     // Actor this channel corresponds to.
    FNetworkGUID ActorNetGUID;          // Actor GUID (useful when we don't have the actor resolved yet).
    float CustomTimeDilation;           // Custom time dilation for this actor.
    double RelevantTime;                // Last time this actor was relevant to client.
    double LastUpdateTime;              // Last time this actor was replicated.
    uint32 SpawnAcked : 1;              // Whether spawn has been acknowledged.
    uint32 bForceCompareProperties : 1; // Force this actor to compare all properties for a single frame.
    uint32 bIsReplicatingActor : 1;     // True when in this channel's ReplicateActor().

    // --- References to other systems/objects ---
    TSharedPtr<FObjectReplicator> ActorReplicator; // The main replicator for the Actor.
    TMap<UObject*, TSharedRef<FObjectReplicator>> ReplicationMap; // Map for sub-object replicators.
    TArray<FInBunch*> QueuedBunches;            // Queued bunches waiting on pending guids to resolve.
    TSet<FNetworkGUID> PendingGuidResolves;     // Guids waiting for resolution.
    TArray<UObject*> CreatedSubObjects;         // Any sub-object we created on this channel.
    EChannelCloseReason QueuedCloseReason;      // Reason for pending channel close.

    UNetConnection* OwningConnection; // The UNetConnection that owns this channel.

    // --- Constructor & Destructor ---
    UActorChannel(UNetConnection* InConnection);
    ~UActorChannel();

    // --- Core UChannel Interface (Simplified) ---
    virtual void Init(UNetConnection* InConnection, int32 InChIndex, uint32 CreateFlags);
    virtual void SetClosingFlag();
    virtual void ReceivedBunch(FInBunch& Bunch);
    virtual void Tick();
    virtual bool CanStopTicking() const;
    virtual int64 Close(EChannelCloseReason Reason);
    virtual FString Describe();

    // --- UActorChannel Specific Interface ---
    UObject* GetActor() const { return Actor; }
    bool IsReliable() const { return true; } // Simplified: always reliable for this conceptual example

    /** Replicate this channel's actor differences. */
    int64 ReplicateActor();

    /** Tells if the actor is ready to be replicated. */
    bool IsActorReadyForReplication() const;

    /** Set this channel's actor to the given actor. */
    void SetChannelActor(UObject* InActor, ESetChannelActorFlags Flags);

    /** Queue a function bunch for this channel to be sent on the next property update. */
    void QueueRemoteFunctionBunch(UObject* CallTarget, UObject* Func, FOutBunch& Bunch); // Func is UObject* for simplicity

    /** Returns true if channel is ready to go dormant. */
    virtual bool ReadyForDormancy(bool debug = false);

    /** Puts the channel in a state to start becoming dormant. */
    virtual void StartBecomingDormant();

    /** Replicates given subobject on this actor channel. */
    bool ReplicateSubobject(UObject* Obj, FOutBunch& Bunch, FReplicationFlags RepFlags);

    // --- Internal Helpers (Simplified) ---
protected:
    /** Attempts to find a valid replicator for the given object. */
    TSharedRef<FObjectReplicator>* FindReplicator(UObject* Obj);

    /** Creates a new object replicator or reuses a dormant one. */
    TSharedRef<FObjectReplicator>& CreateReplicator(UObject* Obj);

    /** Convenience method for finding or creating a replicator. */
    TSharedRef<FObjectReplicator>& FindOrCreateReplicator(UObject* Obj, bool* bOutCreated = nullptr);

    /** Cleans up replicators and clears references. */
    void CleanupReplicators(const bool bKeepReplicators = false);

    /** Handle the replication of subobjects for this actor. */
    bool DoSubObjectReplication(FOutBunch& Bunch, FReplicationFlags& OutRepFlags);
};
