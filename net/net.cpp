#include "net.h"
#include <stdio.h>

Net::Net() :
    m_clientSocket(INVALID_SOCKET),
    m_serverSocket(INVALID_SOCKET)
{
    WSADATA wsaData;
    int result;
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != 0) {
        printf("WSAStartup failed: %d\n", result);
    }
}

Net::~Net()
{

}

void Net::createClient(const char* addr, const char* port)
{
    addrinfo *res = nullptr, *ptr = nullptr, hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int result = getaddrinfo(addr, port, &hints, &res);
    if(result != 0) {
        printf("getaddrinfo failed: %d\n", result);
        WSACleanup();
        return;
    }
    printf("getaddrinfo succeed!!!\n");
    printf("socket family: %d\n", res->ai_family);

    ptr = res;
    m_clientSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(m_clientSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(res);
        WSACleanup();
        return;
    }
    printf("socket() succeed\n");

    //result = bind(m_clientSocket, ptr->ai_addr, ptr->ai_addrlen);
    //if(result == SOCKET_ERROR) {
    //    printf("bind failed with error: %d\n", result);
    //    freeaddrinfo(res);
    //    closesocket(m_clientSocket);
    //    WSACleanup();
    //    return;
    //}
    //printf("bind succeed\n");

	result = connect(m_clientSocket, ptr->ai_addr, ptr->ai_addrlen);
	if (result == SOCKET_ERROR) {
		closesocket(m_clientSocket);
		m_clientSocket = INVALID_SOCKET;
	}

	freeaddrinfo(res);

	if (m_clientSocket == INVALID_SOCKET) {
		printf("unable to connect to server!\n");
		WSACleanup();
		return;
	}
	printf("connect succeed\n");

	std::string str("nihaoa, i'm czy!");
	result = send(m_clientSocket, str.data(), str.size(), 0);
	if (result == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(m_clientSocket);
		WSACleanup();
		return;
	}
	printf("Bytes sent: %ld\n", result);
}

void Net::createServer(std::string& addr, std::string& port)
{
    addrinfo *res = nullptr, *ptr = nullptr, hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int result = getaddrinfo(nullptr, port.data(), &hints, &res);
    if(result != 0) {
        printf("getaddrinfo failed: %d\n", result);
        WSACleanup();
        return;
    }
    addr.append(res->ai_addr->sa_data);
    printf("getaddrinfo succeed!!!\n");
    printf("socket family: %d\n", res->ai_family);
    printf("socket addr: %s\n", addr.data());

    ptr = res;
    m_serverSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(m_serverSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(res);
        WSACleanup();
        return;
    }
    printf("socket() succeed\n"); 

    result = bind(m_serverSocket, res->ai_addr, res->ai_addrlen);
    if(result == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", result);
        freeaddrinfo(res);
        closesocket(m_serverSocket);
        WSACleanup();
        return;
    }
    printf("bind succeed\n");

    freeaddrinfo(res);

    if(listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %ld\n", WSAGetLastError());
        closesocket(m_serverSocket);
        WSACleanup();
        return;
    }
    printf("listen succeed\n");

	m_clientSocket = accept(m_serverSocket, nullptr, nullptr);
	if (m_clientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(m_serverSocket);
		WSACleanup();
		return;
	}
	printf("accept succeed\n");

#define DEFAULT_BUFLEN 512

	char recvBuf[DEFAULT_BUFLEN];
	do {
		memset(recvBuf, 0, DEFAULT_BUFLEN);
		result = recv(m_clientSocket, recvBuf, DEFAULT_BUFLEN, 0);
		if (result > 0) {
			printf("Bytes received: %d: %s\n", result, recvBuf);
		}
		else if (result == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(m_clientSocket);
			WSACleanup();
			return;
		}
	} while (result > 0);
}