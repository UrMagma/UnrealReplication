# GlobalReplication C++ Module

## Overview

Welcome to the GlobalReplication C++ Module! This is a professional, feature-rich replication system inspired by the core concepts of Unreal Engine. It provides a robust framework for synchronizing object properties and remote procedure calls (RPCs) over a network, built from the ground up in modern C++.

The system is designed to be modular, extensible, and easy to integrate into a variety of projects. It includes support for property replication, sub-object replication, RPCs with parameters, and network ownership management.

## ✅ Features

-   **Modern C++ Architecture:** Built using C++20, leveraging modern features for a clean, type-safe, and efficient design.
-   **Property Replication:** Automatically replicates changed properties on objects and their components, minimizing bandwidth usage.
-   **Sub-Object (Component) Replication:** Supports a component-based architecture where sub-objects have their own replicated properties.
-   **RPCs with Parameters:** A powerful RPC system that allows functions with any number of serializable parameters to be called remotely.
-   **Network Ownership:** A full-featured system allowing clients to request and be granted authority over network objects.
-   **Customizable Data Types:** Provides `FString` and `TArray<T>` as serializable alternatives to `std::string` and `std::vector`.
-   **Cross-Platform Build System:** Uses CMake for easy, cross-platform building on Windows, Linux, and macOS.

## ⚙️ How to Build and Run

The project uses CMake, which makes it simple to build and run the example application.

### Prerequisites
- A C++20 compatible compiler (e.g., GCC 10+, Clang 12+, MSVC v19.29+).
- CMake (version 3.10 or later).

### Build Steps
From the root directory of the project, run the following commands:

```bash
# 1. Configure the project and generate build files
cmake . -B build

# 2. Build the project
cmake --build build

# 3. Run the example application
./build/Example
```

## 🔬 Example Walkthrough (Proof of Work)

The `main.cpp` file contains a test case that demonstrates the sub-object replication system. Here is a walkthrough of what the test does and what the output proves:

1.  **Setup:**
    -   A "server-side" `MyReplicatedObject` is created.
    -   A `MyPlayerStatsComponent` is created and attached to the main object.
    -   Properties on both the main object (`PlayerName`) and the component (`Health`, `Stamina`) are changed from their default values.

2.  **Manual Serialization:**
    -   The test manually creates two property update packets, simulating what the `ReplicationDriver` would send over a real network.
    -   One packet contains the serialized data for the main object.
    -   The other packet contains the serialized data for the component, correctly identified with its sub-object index.

3.  **Client-Side Simulation:**
    -   A "client-side" object, component, and a test driver are created.
    -   The `HandlePropertyUpdate` method of the test driver is called for each packet, simulating a client receiving the data.

4.  **Verification:**
    -   The test prints the final state of the client's object and component.
    -   It then compares the properties of the client's objects to the server's objects.

### Expected Output
When you run the example, you will see the following output, which proves that the properties of both the main object and its sub-object were correctly replicated to the client-side instance:

```
--- Sub-Object Replication Test ---

[Server] Initial state:
  NetID: 101
  PlayerName: ServerJules
  LastMessage:
    Health: 50, Stamina: 75

[Client] Initial state:
  NetID: 101
  PlayerName:
  LastMessage:
    Health: 100, Stamina: 100

[Client] Applying property updates...
Applied property update for object 101, sub-object 0
Applied property update for object 101, sub-object 1

[Client] Final state:
  NetID: 101
  PlayerName: ServerJules
  LastMessage:
    Health: 50, Stamina: 75

--- Verification ---
SUCCESS: All properties replicated correctly.

--- Test Complete ---
```

## 🚀 Future Work

While the current system is robust, here are some features that could be added in the future:

-   **Dormancy and Relevance:** A system to further optimize bandwidth by not replicating objects that are far away or not changing for long periods.
-   **Advanced Network Features:** Improving the socket layer with features like reliability (guaranteed packet delivery), congestion control, and packet ordering.
-   **Server-Side Property Deserialization:** Implementing the logic for the server to process property updates from clients, for a true two-way data flow.

## 🙏 Credits

-   **Creator:** UrMagma
-   **Lead Engineer:** Jules
