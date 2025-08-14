#include "GlobalReplication/Public/ReplicationConnection.h"
#include "GlobalReplication/Public/Socket.h"
#include <algorithm>
#include <iostream>

ReplicationConnection::ReplicationConnection(const sockaddr_in& InAddr)
    : Address(InAddr)
{
}

void ReplicationConnection::SendData(FSocket& Socket, const std::vector<uint8_t>& Data)
{
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(Address.sin_addr), ip, INET_ADDRSTRLEN);
    Socket.SendTo(Data, ip, ntohs(Address.sin_port));
}

void ReplicationConnection::SendRPC(const FRPCData& Data)
{
    std::cout << "Queueing RPC for object " << Data.NetID << ", function " << Data.FunctionName << std::endl;
    OutgoingRPCBuffer.push(Data);
}

void ReplicationConnection::AddReplicatedObject(IReplicatedObject* Obj)
{
    if (Obj)
    {
        ReplicatedObjects[Obj->GetNetID()] = Obj;
    }
}

void ReplicationConnection::RemoveReplicatedObject(IReplicatedObject* Obj)
{
    if (Obj)
    {
        ReplicatedObjects.erase(Obj->GetNetID());
    }
}
