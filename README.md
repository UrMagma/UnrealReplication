# GlobalReplication Module

A generic, extensible, and easy-to-integrate replication system built with modern C++.

## Overview

The GlobalReplication module provides a basic framework for replicating object state over a network. It is designed to be engine-agnostic and can be easily integrated into various server projects. The system is built with a focus on modularity and extensibility, using an interface-based design that allows for easy customization and expansion.

## Features

- **Modular Design:** The entire system is self-contained within the `GlobalReplication` directory.
- **Interface-Based:** Core components are defined as interfaces (`I...` classes), making the system flexible and testable.
- **Modern C++:** Uses modern C++ features like smart pointers for safe and efficient memory management.
- **Standard Build System:** Comes with a `CMakeLists.txt` file for easy, cross-platform building.
- **Clear Example:** Includes a `main.cpp` that demonstrates how to use the module.

## Core Concepts

The system is built around three core interfaces:

- **`IReplicationDriver`**: The main hub of the replication system. It manages all active connections and drives the replication process on each "tick".
- **`IReplicationConnection`**: Represents a single connection to a client. It manages the list of objects that are being replicated to that client.
- **`IReplicatedObject`**: An interface that must be implemented by any object that you want to be replicated. It defines how an object's state is serialized.

Serialization is handled by the `FArchive` class, which provides a simple interface for writing data to a buffer.

## How to Build

The project uses CMake to generate build files for your platform.

```bash
# Create a build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile the project
make
```

This will produce an executable named `Example` in the `build` directory.

## How to Use

Here is a simple example of how to integrate and use the `GlobalReplication` module. This code is taken from `main.cpp`.

First, you need to include the main header for the module:

```cpp
#include "GlobalReplication/Public/GlobalReplication.h"
#include "GlobalReplication/Public/ReplicationDriver.h"
#include "GlobalReplication/Public/ReplicationConnection.h"
```

Next, create a class that implements the `IReplicatedObject` interface. This class will define the data that you want to replicate.

```cpp
class MyReplicatedObject : public IReplicatedObject
{
public:
    MyReplicatedObject(uint64_t InNetID, float InX, float InY, int InHealth)
        : NetID(InNetID), x(InX), y(InY), health(InHealth)
    {
    }

    // This method is called to serialize the object's state.
    virtual void Serialize(FArchive& Ar) override
    {
        Ar.Serialize(&NetID, sizeof(NetID));
        Ar.Serialize(&x, sizeof(x));
        Ar.Serialize(&y, sizeof(y));
        Ar.Serialize(&health, sizeof(health));
    }

    virtual uint64_t GetNetID() const override
    {
        return NetID;
    }

private:
    uint64_t NetID;
    float x;
    float y;
    int health;
};
```

Finally, in your main application logic, you can create a `ReplicationDriver`, add connections, and replicate objects.

```cpp
int main()
{
    // 1. Create the replication driver
    auto Driver = std::make_shared<ReplicationDriver>();

    // 2. Create a connection
    auto Connection = std::make_shared<ReplicationConnection>();
    Driver->AddConnection(Connection);

    // 3. Create some replicated objects
    MyReplicatedObject Obj1(101, 10.0f, 20.0f, 100);
    MyReplicatedObject Obj2(102, 30.0f, 40.0f, 80);

    // 4. Add the objects to the connection's replication list
    Connection->AddReplicatedObject(&Obj1);
    Connection->AddReplicatedObject(&Obj2);

    // 5. In your main loop, tick the driver to perform replication
    Driver->Tick(0.016f);

    return 0;
}
```

## Future Improvements

This system is a foundation that can be extended with more advanced features:

- **Network Transport:** The current `ReplicationConnection` uses simple in-memory buffers. This can be extended to use a real network transport layer like UDP sockets.
- **Object Prioritization:** Implement a system to prioritize which objects get replicated based on factors like distance, importance, or last update time.
- **Dormancy and Relevance:** Add support for object dormancy (stopping replication for objects that are not changing) and relevance (only replicating objects that are relevant to a specific client).
- **Remote Procedure Calls (RPCs):** Implement a system for calling functions on remote objects.
