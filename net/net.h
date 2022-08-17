#ifndef NET_NET_H
#define NET_NET_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "export.h"
#include <string>

class NET_EXPORT Net
{
public:
    Net();
    ~Net();

    void createClient(const char* addr, const char* port);
    void createServer(std::string& addr, std::string& port);

protected:
    SOCKET m_clientSocket;
    SOCKET m_serverSocket;
};

#endif