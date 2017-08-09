#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")

#endif

#include "TCPIP_Connector.h"

void TCPIP_Connector::write(const std::string& s)
{
	//TODO
}

std::string TCPIP_Connector::read()
{
	//TODO
	return std::string();
}

bool TCPIP_Connector::isConnected()
{
	//TODO
	return false;
}

TCPIP_Connector::TCPIP_Connector(const std::string& ip, uint16_t port)
	: ip(ip), port(port)
{
	//TODO

#ifdef _WIN32
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
		//TODO: throw exception
	}


	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

#define DEFAULT_PORT "27015"

	// Resolve the server address and port
	iResult = getaddrinfo(ip.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;	

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

#endif

}
