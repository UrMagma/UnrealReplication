#pragma once

#include <vector>
#include <cstdint>
#include <memory>

// Forward declarations
class FArchive;
class IReplicatedObject;
class IReplicationConnection;
class IReplicationDriver;

/**
 * @brief A virtual archive for serializing data.
 * This is a simplified version of Unreal Engine's FArchive.
 */
class FArchive
{
public:
    virtual ~FArchive() = default;
    virtual void Serialize(void* Data, int64_t Num) = 0;
    // Add more methods as needed, e.g., for seeking, telling, etc.
};

/**
 * @brief Interface for an object that can be replicated.
 */
class IReplicatedObject
{
public:
    virtual ~IReplicatedObject() = default;

    /**
     * @brief Serializes the object's state into an archive.
     * @param Ar The archive to serialize to/from.
     */
    virtual void Serialize(FArchive& Ar) = 0;

    /**
     * @brief Gets a unique identifier for this object.
     * @return A unique 64-bit integer ID.
     */
    virtual uint64_t GetNetID() const = 0;
};

/**
 * @brief Interface for a single client connection.
 */
class IReplicationConnection
{
public:
    virtual ~IReplicationConnection() = default;

    /**
     * @brief Sends data over the connection.
     * @param Data The raw byte data to send.
     */
    virtual void SendData(const std::vector<uint8_t>& Data) = 0;

    /**
     * @brief Checks if there is pending data to be received.
     * @return True if there is data, false otherwise.
     */
    virtual bool HasPendingData() const = 0;

    /**
     * @brief Gets the pending data from the connection.
     * @return A vector of bytes containing the received data.
     */
    virtual std::vector<uint8_t> GetPendingData() = 0;

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
