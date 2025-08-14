#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <iostream>

class FArchive;
class IReplicatedObject;

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
    std::vector<uint8_t> Parameters;

    void Serialize(FArchive& Ar);
};


#include <tuple>
#include <utility>

// Creates a thunk (a generic function wrapper) for a specific member function.
// This thunk knows how to deserialize arguments from an archive and call the member function.
template<typename T, typename... Args>
RPC_Thunk CreateThunk(void (T::*Func)(Args...))
{
    return [Func](IReplicatedObject* Obj, FArchive& Ar) {
        // Create a tuple to hold the deserialized arguments.
        // std::decay_t is used to handle types like 'const FString&' correctly, converting them to 'FString'.
        std::tuple<std::decay_t<Args>...> InArgs;

        // Use a C++17 fold expression to deserialize all arguments from the archive into the tuple.
        std::apply([&](auto&... args){ ( (Ar << args), ...); }, InArgs);

        // Use std::apply to call the member function pointer with the arguments from the tuple.
        std::apply([&](auto&... args){ (static_cast<T*>(Obj)->*Func)(std::forward<Args>(args)...); }, InArgs);
    };
}

// A simple macro to register a member function as an RPC.
// This should be called in the constructor of the replicated object.
#define REGISTER_RPC(ClassName, FuncName) \
    RPCRegistry::Get().Register(#ClassName "::" #FuncName, CreateThunk(&ClassName::FuncName))
