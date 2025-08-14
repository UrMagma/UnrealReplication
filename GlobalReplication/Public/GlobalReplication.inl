#pragma once

#include "GlobalReplication/Public/MemoryArchive.h" // Include the full definition of FMemoryArchive

template<typename... Args>
void IReplicatedObject::SendRPC(const std::string& RpcName, Args&&... args)
{
    if (HasAuthority())
    {
        // If we already have authority, we could execute the RPC directly.
        // However, the canonical flow is to always go through the server.
        // For this implementation, we'll assume SendRPC is only called on non-authoritative clients.
        return;
    }

    if (GetOwningConnection())
    {
        std::vector<uint8_t> ParamBuffer;
        FMemoryArchive Ar(ParamBuffer, true);
        // Use a C++17 fold expression to serialize all arguments into the archive.
        // Note the use of std::forward to handle rvalue references correctly.
        ( (Ar << std::forward<Args>(args)), ... );

        FRPCData RpcData;
        RpcData.NetID = GetNetID();
        RpcData.FunctionName = RpcName;
        RpcData.Parameters = ParamBuffer;

        GetOwningConnection()->SendRPC(RpcData);
    }
}

template<typename... Args>
void IReplicatedObject::CallRPC_OnClient(const std::string& RpcName, Args&&... args)
{
    if (!HasAuthority())
    {
        return; // Can only be called from the server/authority
    }

    if (auto Conn = GetOwningConnection())
    {
        std::vector<uint8_t> ParamBuffer;
        FMemoryArchive Ar(ParamBuffer, true);
        ( (Ar << std::forward<Args>(args)), ... );

        FRPCData RpcData;
        RpcData.NetID = GetNetID();
        RpcData.FunctionName = RpcName;
        RpcData.Parameters = ParamBuffer;

        Conn->SendRPC(RpcData);
    }
}
