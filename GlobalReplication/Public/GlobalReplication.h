#pragma once

#include <vector>
#include <cstdint>
#include <memory>

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

protected:
    bool bIsSaving;
};

#include "ReplicatedProperty.h"

/**
 * @brief Interface for an object that can be replicated.
 */
class IReplicatedObject
{
public:
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

    /**
     * @brief Called to register all replicated sub-objects.
     */
    virtual void RegisterReplicatedSubObjects() {}

    void AddComponent(UReplicatedComponent* Comp)
    {
        if (Comp)
        {
            SubObjects.push_back(Comp);
        }
    }

    std::vector<FRepPropertyBase*> ReplicatedProperties;
    std::vector<UReplicatedComponent*> SubObjects;
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
     * @param RPCData The raw byte data for the RPC.
     */
    virtual void SendRPC(const std::vector<uint8_t>& RPCData) = 0;

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
