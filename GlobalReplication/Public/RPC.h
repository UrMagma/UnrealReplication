#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <vector>
#include "GlobalReplication.h" // For FArchive
#include "MemoryArchive.h" // For FMemoryArchive

class IReplicatedObject;
class IReplicationConnection;

// A function that can call an RPC with serialized parameters.
using RPC_Thunk = std::function<void(IReplicatedObject*, FArchive&)>;

/**
 * @brief A singleton registry for all RPCs.
 */
class RPCRegistry
{
public:
    static RPCRegistry& Get()
    {
        static RPCRegistry Instance;
        return Instance;
    }

    void Register(const std::string& Name, RPC_Thunk Thunk)
    {
        std::cout << "Registering RPC: " << Name << std::endl;
        Thunks[Name] = Thunk;
    }

    RPC_Thunk Find(const std::string& Name)
    {
        auto It = Thunks.find(Name);
        if (It != Thunks.end())
        {
            return It->second;
        }
        return nullptr;
    }

private:
    RPCRegistry() = default;
    std::unordered_map<std::string, RPC_Thunk> Thunks;
};

/**
 * @brief A helper struct to register an RPC at static initialization time.
 */
struct RPCRegistrar
{
    RPCRegistrar(const std::string& Name, RPC_Thunk Thunk)
    {
        RPCRegistry::Get().Register(Name, Thunk);
    }
};

/**
 * @brief Data for an RPC call.
 */
struct FRPCData
{
    uint64_t NetID;
    std::string FunctionName;

    void Serialize(FArchive& Ar)
    {
        if (Ar.IsSaving())
        {
            size_t NameLen = FunctionName.size();
            Ar.Serialize(&NetID, sizeof(NetID));
            Ar.Serialize(&NameLen, sizeof(NameLen));
            Ar.Serialize((void*)FunctionName.data(), NameLen);
        }
        else
        {
            size_t NameLen;
            Ar.Serialize(&NetID, sizeof(NetID));
            Ar.Serialize(&NameLen, sizeof(NameLen));
            FunctionName.resize(NameLen);
            Ar.Serialize((void*)FunctionName.data(), NameLen);
        }
    }
};


// Macro to declare an RPC in a header file.
#define DECLARE_RPC(RpcFunc) \
    void RpcFunc(); \
    static RPCRegistrar Registrar_##RpcFunc;

// Macro to implement an RPC in a .cpp file.
#define IMPLEMENT_RPC(ClassName, RpcFunc) \
    void ClassName::RpcFunc() \
    { \
        if (HasAuthority()) \
        { \
            std::cout << "Executing RPC on authority: " #RpcFunc << std::endl; \
        } \
        else \
        { \
            /* This is where we would serialize and send the RPC */ \
            /* For the example, this is done manually in main.cpp */ \
        } \
    } \
    RPCRegistrar ClassName::Registrar_##RpcFunc(#ClassName "::" #RpcFunc, \
        [](IReplicatedObject* Obj, FArchive& Ar) \
        { \
            static_cast<ClassName*>(Obj)->RpcFunc(); \
        });
