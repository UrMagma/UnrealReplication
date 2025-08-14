#pragma once

#include <cstdint>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif

/**
 * @brief A wrapper class for a UDP socket.
 */
class FSocket
{
public:
    FSocket();
    ~FSocket();

    bool Create();
    bool Bind(const std::string& Address, uint16_t Port);
    bool SendTo(const std::vector<uint8_t>& Data, const std::string& Address, uint16_t Port);
    int32_t RecvFrom(std::vector<uint8_t>& Buffer, sockaddr_in& From);
    void Close();
    void SetNonBlocking(bool bIsNonBlocking);

private:
#if defined(_WIN32) || defined(_WIN64)
    SOCKET SocketHandle;
    static bool bWSAIsInitialized;
#else
    int SocketHandle;
#endif
};
