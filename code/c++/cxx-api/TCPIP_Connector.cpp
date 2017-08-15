#if (defined(__linux__) || defined(__unix__))

#define SOCKET_ERROR 				(-1)
#define closesocket(...)			close(__VA_ARGS__)

/* shutdown() ports */
#define SD_RECEIVE					SHUT_RD
#define SD_SEND						SHUT_WR
#define SD_BOTH						SHUT_RDWR

#define WSAGetLastError()			errno

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#endif /* ﻿(defined(__linux__) || defined(__unix__)) */

#include <cstring>

#include "trackPlatformAllExceptions.h"
#include "TCPIP_Connector.h"

void TCPIP_Connector::write(const std::string& s)
{
	// Send an initial buffer (returns byte sended)
#ifdef _WIN32
	int iResult = send(connectedSocket, s.c_str(), static_cast<int>(s.length()), 0);
#else /* _WIN32 */
	int iResult = send(connectedSocket, s.c_str(), s.length(), 0);
#endif /* _WIN32 */
	if (iResult == SOCKET_ERROR) {
		throw SocketSendException(WSAGetLastError());
	}
}

std::string TCPIP_Connector::read()
{
	std::string answer;
	char recvbuf[onePacketMaxSize];

	int iResult;

	do {
		// Check if something is already in buffer (and wait `microsecondsToWaitAnswer` if required)
		timeval tval = { 0, microsecondsToWaitAnswer };

#ifdef _WIN32
		fd_set readSockets = { 1, { connectedSocket } };
		iResult = select(0, &readSockets, NULL, NULL, &tval);
#else /* _WIN32 */
		fd_set readSockets;
		FD_ZERO(&readSockets);
		FD_SET(connectedSocket, &readSockets);
		iResult = select(connectedSocket + 1, &readSockets, NULL, NULL, &tval);
#endif /* _WIN32 */
		if (iResult == SOCKET_ERROR)
		{
			throw SocketException(WSAGetLastError());
		}
		if (iResult == 0)
		{
			break;
		}

		// Receive data until the server closes the connection
		iResult = recv(connectedSocket, recvbuf, sizeof(recvbuf), 0);
		if (iResult < 0)
		{
			throw SocketReceiveException(WSAGetLastError());
		}

		answer += std::string(recvbuf, iResult);
	} while (iResult > 0);

	return answer;
}

void TCPIP_Connector::configureSocket()
{
	struct addrinfo hints;

	// Configure socket
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;					/* AF_UNSPEC for IPv6 or IPv4 (automatically); AF_INET6 for IPv6; AF_INET for IPv4 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	int iResult = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &addressInfo);
	if (iResult != 0) {
		addressInfo = nullptr;
		throw BadAddressOrPortException(iResult);
	}
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

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	struct addrinfo* ptr = addressInfo;

	// Create a SOCKET for connecting to server
	connectedSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (connectedSocket == INVALID_SOCKET) {
		throw SocketException(WSAGetLastError());
	}

	// Connect to server.
#ifdef _WIN32
	int iResult = ::connect(connectedSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
#else /* _WIN32 */
	int iResult = ::connect(connectedSocket, addressInfo->ai_addr, addressInfo->ai_addrlen);
#endif /* _WIN32 */
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
#ifdef _WIN32
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		throw WSAStartupException(iResult);
	}
#endif

	configureSocket();
	TCPIP_Connector::connect();
}

TCPIP_Connector::~TCPIP_Connector()
{
	TCPIP_Connector::disconnect();
	if (addressInfo)
	{
		freeaddrinfo(addressInfo);
	}
#ifdef _WIN32
	WSACleanup();
#endif
}

