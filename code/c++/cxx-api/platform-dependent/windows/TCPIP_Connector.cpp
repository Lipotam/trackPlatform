#ifndef _WIN32

#error This source file must be used only on Windows desktop platforms (win32) 

#else /* _WIN32 */

#include "WSAStartupException.h"
#include "BadAddressOrPortException.h"
#include "SocketException.h"
#include "SocketShutdownException.h"
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

void TCPIP_Connector::closeSocket()
{
	if (connectedSocket != INVALID_SOCKET)
	{
		closesocket(connectedSocket);
		connectedSocket = INVALID_SOCKET;
	}
}

bool TCPIP_Connector::isConnected()
{
	return isConnected_private;
}

void TCPIP_Connector::connect()
{
	if (isConnected_private) {
		return;
	}

	struct addrinfo *ptr = nullptr, hints;

	// Configure socket
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;					/* AF_UNSPEC for IPv6 or IPv4 (automatically); AF_INET6 for IPv6; AF_INET for IPv4 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	int iResult = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &addressInfo);
	if (iResult != 0) {
		addressInfo = nullptr;
		throw BadAddressOrPortException(iResult);
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = addressInfo;

	// Create a SOCKET for connecting to server
	connectedSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (connectedSocket == INVALID_SOCKET) {
		throw SocketException(WSAGetLastError());
	}

	// Connect to server.
	iResult = ::connect(connectedSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (iResult == SOCKET_ERROR) {
		closeSocket();
	}
	else
	{
		isConnected_private = true;
	}
}

void TCPIP_Connector::disconnect()
{
	if (!isConnected_private)
	{
		return;
	}

	// shutdown the sending and recieving data by socket
	int iResult = shutdown(connectedSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		throw SocketShutdownException(WSAGetLastError());
	}

	closeSocket();
	isConnected_private = false;
}

TCPIP_Connector::TCPIP_Connector(const std::string& ip, uint16_t port)
	: ip(ip), port(port)
{
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		throw WSAStartupException(iResult);
	}

	TCPIP_Connector::connect();
}

TCPIP_Connector::~TCPIP_Connector()
{
	TCPIP_Connector::disconnect();
	if (addressInfo)
	{
		freeaddrinfo(addressInfo);
	}
	WSACleanup();
}

#endif /* _WIN32 */
