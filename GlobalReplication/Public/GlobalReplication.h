#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "DataTypes.h"
#include "RPC.h"

enum class EPacketType : uint8_t
{
    Property,
    RPC,
};

// Forward declarations
class FArchive;
class IReplicatedObject;
class UReplicatedComponent;
class IReplicationConnection;
class IReplicationDriver;

// Forward declarations for serialization operators
class FString;
template<typename T>
class TArray;

/**
 * @brief A virtual archive for serializing data.
 * This is a simplified version of Unreal Engine's FArchive.
 */
class FArchive
{
public:
    FArchive(bool bInIsSaving) : bIsSaving(bInIsSaving) {}
    virtual ~FArchive() = default;
    virtual void Serialize(void* Data, int64_t Num) = 0;

    bool IsSaving() const { return bIsSaving; }

    // Serialization operators for fundamental types
    FArchive& operator<<(uint8_t& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(uint32_t& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(uint64_t& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(int32_t& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(int64_t& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(float& Val) { Serialize(&Val, sizeof(Val)); return *this; }
    FArchive& operator<<(bool& Val) { Serialize(&Val, sizeof(Val)); return *this; }

    // Serialization operators for complex types
    FArchive& operator<<(FString& Val) { Val.Serialize(*this); return *this; }
    template<typename T>
    FArchive& operator<<(TArray<T>& Val) { Val.Serialize(*this); return *this; }

protected:
    bool bIsSaving;
};

#include "ReplicatedProperty.h"

/**
 * @brief A base class for any object that has replicated properties.
 */
class FReplicatedObjectBase
{
public:
    virtual ~FReplicatedObjectBase() = default;

    /**
     * @brief Gets the list of replicated properties for this object.
     * @return A vector of pointers to the replicated properties.
     */
    const std::vector<FRepPropertyBase*>& GetReplicatedProperties() const { return ReplicatedProperties; }

protected:
    /**
     * @brief Called to register all replicated properties.
     * This should be implemented by derived classes to add their FRepProperty members to the ReplicatedProperties list.
     */
    virtual void RegisterReplicatedProperties() = 0;

    std::vector<FRepPropertyBase*> ReplicatedProperties;
};


/**
 * @brief Interface for an object that can be replicated.
 */
class IReplicatedObject : public FReplicatedObjectBase
{
public:
    static void RegisterBuiltInRPCs();

    virtual ~IReplicatedObject() = default;

    /**
     * @brief Gets a unique identifier for this object.
     * @return A unique 64-bit integer ID.
     */
    virtual uint64_t GetNetID() const = 0;

    /**
     * @brief Gets the replication priority of this object.
     * Higher values are replicated first.
     * @return The priority value.
     */
    virtual float GetPriority() const = 0;

    /**
     * @brief Checks if the current instance has network authority over this object.
     * @return True if this instance has authority, false otherwise.
     */
    virtual bool HasAuthority() const = 0;

    /**
     * @brief Sets whether this object can have its ownership transferred to a client.
     * @param bCanBeOwned True if ownership can be transferred.
     */
    void SetAllowClientOwnership(bool bCanBeOwned) { bAllowClientOwnership = bCanBeOwned; }
    bool CanBeOwnedByClient() const { return bAllowClientOwnership; }

    // --- Built-in RPCs for ownership ---
    virtual void Server_RequestOwnership();
    virtual void Client_GainedOwnership();
    virtual void Client_LostOwnership();

    void SetOwningConnection(std::shared_ptr<IReplicationConnection> Conn) { OwningConnection = Conn; }
    std::shared_ptr<IReplicationConnection> GetOwningConnection() const { return OwningConnection; }

    /**
     * @brief Sends an RPC from a non-authoritative instance to the authoritative instance.
     * @param RpcName The registered name of the RPC (e.g., "ClassName::FunctionName").
     * @param args The arguments to pass to the RPC.
     * @note The implementation for this template function is in GlobalReplication.inl.
     *       You must #include "GlobalReplication/Public/GlobalReplication.inl" in the .cpp file where you call this.
     */
    template<typename... Args>
    void SendRPC(const std::string& RpcName, Args&&... args);

    /**
     * @brief Queues an RPC to be called on the client that owns this object.
     * This should only be called from the authoritative instance.
     */
    template<typename... Args>
    void CallRPC_OnClient(const std::string& RpcName, Args&&... args);

    void AddComponent(UReplicatedComponent* Comp);

protected:
    /**
     * @brief Called to register all replicated sub-objects.
     */
    virtual void RegisterReplicatedSubObjects() {}

    std::vector<UReplicatedComponent*> SubObjects;
    std::shared_ptr<IReplicationConnection> OwningConnection;
    bool bAllowClientOwnership = false;

public:
    const std::vector<UReplicatedComponent*>& GetSubObjects() const { return SubObjects; }
};

class FSocket;

/**
 * @brief Interface for a single client connection.
 */
class IReplicationConnection
{
public:
    virtual ~IReplicationConnection() = default;

    /**
     * @brief Sends data over the connection using the provided socket.
     * @param Socket The socket to send data on.
     * @param Data The raw byte data to send.
     */
    virtual void SendData(FSocket& Socket, const std::vector<uint8_t>& Data) = 0;

    /**
     * @brief Sends an RPC over the connection.
     * @param Data The RPC data payload.
     */
    virtual void SendRPC(const FRPCData& Data) = 0;

    /**
     * @brief Adds an object to be replicated over this connection.
     * @param Obj The object to replicate.
     */
    virtual void AddReplicatedObject(IReplicatedObject* Obj) = 0;

    /**
     * @brief Removes an object from replication on this connection.
     * @param Obj The object to stop replicating.
     */
    virtual void RemoveReplicatedObject(IReplicatedObject* Obj) = 0;
};

/**
 * @brief The main driver for the replication system.
 */
class IReplicationDriver
{
public:
    virtual ~IReplicationDriver() = default;

    /**
     * @brief Adds a new connection to be managed by the driver.
     * @param Conn The connection to add.
     */
    virtual void AddConnection(std::shared_ptr<IReplicationConnection> Conn) = 0;

    /**
     * @brief Removes a connection from the driver.
     * @param Conn The connection to remove.
     */
    virtual void RemoveConnection(std::shared_ptr<IReplicationConnection> Conn) = 0;

    /**
     * @brief Ticks the replication system.
     * @param DeltaTime The time in seconds since the last tick.
     */
    virtual void Tick(float DeltaTime) = 0;
};
