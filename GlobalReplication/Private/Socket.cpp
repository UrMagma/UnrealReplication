#include "GlobalReplication/Public/Socket.h"
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
bool FSocket::bWSAIsInitialized = false;
#endif

FSocket::FSocket() : SocketHandle(-1)
{
#if defined(_WIN32) || defined(_WIN64)
    if (!bWSAIsInitialized)
    {
        WSADATA WsaData;
        if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0)
        {
            std::cerr << "Failed to initialize Winsock" << std::endl;
        }
        else
        {
            bWSAIsInitialized = true;
        }
    }
#endif
}

FSocket::~FSocket()
{
    Close();
}

bool FSocket::Create()
{
    SocketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SocketHandle <= 0)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    return true;
}

bool FSocket::Bind(const std::string& Address, uint16_t Port)
{
    sockaddr_in Addr;
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Address.c_str(), &Addr.sin_addr);

    if (bind(SocketHandle, (const sockaddr*)&Addr, sizeof(Addr)) < 0)
    {
        std::cerr << "Failed to bind socket" << std::endl;
        return false;
    }
    return true;
}

bool FSocket::SendTo(const std::vector<uint8_t>& Data, const std::string& Address, uint16_t Port)
{
    sockaddr_in Addr;
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(Port);
    inet_pton(AF_INET, Address.c_str(), &Addr.sin_addr);

    int32_t SentBytes = sendto(SocketHandle, (const char*)Data.data(), Data.size(), 0, (sockaddr*)&Addr, sizeof(Addr));
    if (SentBytes != Data.size())
    {
        std::cerr << "Failed to send data" << std::endl;
        return false;
    }
    return true;
}

int32_t FSocket::RecvFrom(std::vector<uint8_t>& Buffer, sockaddr_in& From)
{
    socklen_t FromLen = sizeof(From);
    int32_t BytesRead = recvfrom(SocketHandle, (char*)Buffer.data(), Buffer.size(), 0, (sockaddr*)&From, &FromLen);
    return BytesRead;
}

void FSocket::Close()
{
    if (SocketHandle > 0)
    {
#if defined(_WIN32) || defined(_WIN64)
        closesocket(SocketHandle);
#else
        close(SocketHandle);
#endif
        SocketHandle = -1;
    }
}

void FSocket::SetNonBlocking(bool bIsNonBlocking)
{
#if defined(_WIN32) || defined(_WIN64)
    u_long NonBlocking = bIsNonBlocking ? 1 : 0;
    ioctlsocket(SocketHandle, FIONBIO, &NonBlocking);
#else
    int Flags = fcntl(SocketHandle, F_GETFL, 0);
    if (bIsNonBlocking)
    {
        fcntl(SocketHandle, F_SETFL, Flags | O_NONBLOCK);
    }
    else
    {
        fcntl(SocketHandle, F_SETFL, Flags & ~O_NONBLOCK);
    }
#endif
}
