# Project: GlobalReplication Module - Status & Roadmap

## ✅ What We've Done (Completed Tasks)

We have successfully built the foundation of a professional, feature-rich replication system. Here are the key features that are complete and working:

- [x] **Complete Project Restructuring:** The original codebase has been replaced with a clean, modular C++ project structure.
- [x] **Core System Design:** The system is built on a foundation of interfaces (`IReplicationDriver`, `IReplicationConnection`, `IReplicatedObject`) for maximum flexibility and extensibility.
- [x]  **Sub-object Replication:** 
- [x] **Network Transport Layer:** A basic UDP socket layer has been implemented, allowing the system to send and receive data over the network.
- [x] **Efficient Property Replication:**
    - **Property Diffing:** The system only sends properties that have changed, significantly reducing bandwidth.
    - **Object Prioritization:** The replication driver intelligently prioritizes more important objects to ensure they are updated first.
- [x] **RPC Framework:** A basic framework for Remote Procedure Calls (RPCs) is in place, allowing for parameter-less functions to be called on remote objects.
- [x] **Serializable Data Types:** Core data types `FString` (for strings) and `TArray<T>` (for dynamic arrays) have been implemented, with robust serialization support.
- [x] **Build System:** The project uses CMake for easy, cross-platform building.
- [x] **Example Application:** A `main.cpp` file demonstrates all the core features and serves as a testbed.
- [x] **Documentation:** A `README.md` file has been created to explain the project.

## ⚙️ How It Works (Architecture Overview)

The system is designed around a few core concepts:

1.  **The `ReplicationDriver`:** This is the main hub of the system. It manages all client connections and runs the main replication loop (the "tick").
2.  **The `ReplicationConnection`:** This represents a single connection to a client. It knows which objects need to be replicated to that specific client.
3.  **The `IReplicatedObject` Interface:** Any object you want to replicate must implement this interface. It uses a property system (`FRepProperty<T>`) to automatically track which variables have changed.
4.  **The `FArchive` Serialization System:** Data is serialized into a byte buffer for network transport using a custom `FArchive` class. This system supports fundamental types as well as complex types like `FString` and `TArray`.
5.  **The Replication Loop:** On each tick, the `ReplicationDriver`:
    - Gathers all the "dirty" (changed) objects for each connection.
    - Sorts these objects by priority.
    - Serializes the changed properties into a buffer using `FArchive`.
    - Sends the buffer over the network.
6.  **The RPC Flow:**
    - You can declare RPCs in your `IReplicatedObject` classes using macros.
    - When an RPC is called on a client, the system automatically serializes the function call and sends it to the server.
    - The server receives the RPC, finds the correct object, and executes the function.

### Core Data Types

To facilitate easy and robust replication, the system provides two core data types that mirror those found in Unreal Engine:

-   `FString`: A wrapper around `std::string` that is fully serializable by the `FArchive` system.
-   `TArray<T>`: A template class that wraps `std::vector<T>` and is also fully serializable. It can contain any other serializable type, including other `TArray`s or `FString`s.

These types should be used within your `IReplicatedObject` classes for any string or dynamic array properties that you wish to replicate.

## 🚀 What's Next (Roadmap)

Here are the next steps to make the system even more powerful and feature-complete:
- [x] **RPCs with Parameters:**
    - **Goal:** Extend the RPC framework to support parameters of various types.
    - **Note:** This feature has been implemented using C++20 templates for a clean and powerful solution.
- [ ] **Dormancy and Relevance:**
    - **Goal:** Further optimize bandwidth by not replicating objects that are not changing or are not relevant to a client (e.g., too far away).
- [ ] **Network Ownership:**
    - **Goal:** Implement logic for transferring network authority of objects between clients (e.g., for picking up an item).
- [ ] **Advanced Network Features:**
    - **Goal:** Improve the socket layer with features like reliability (guaranteed packet delivery), congestion control, and packet ordering.
