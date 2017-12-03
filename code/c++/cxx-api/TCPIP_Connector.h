#ifndef _TCPIP_CONNECTOR_H_
#define _TCPIP_CONNECTOR_H_

#if defined(_WIN32)

/* WinAPI include */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")

#endif /* _WIN32 */

#if (defined(__linux__) || defined(__unix__))

#define SOCKET 						int
#define INVALID_SOCKET 				(-1)

#endif /* (defined(__linux__) || defined(__unix__)) */

#include "TrackPlatform_BasicConnector.h"

class TCPIP_Connector : public TrackPlatform_BasicConnector
{
	std::string ip;
	uint16_t port;

	std::string receivedBuffer;

	static const uint16_t onePacketMaxSize = 512;
	static const int32_t microsecondsToWaitAnswer = 400000;

#ifdef _WIN32
	WSADATA wsaData;
#endif /* _WIN32 */
	struct addrinfo *addressInfo = nullptr;
	SOCKET connectedSocket = INVALID_SOCKET;

	bool isSocketConnected = false;

	void configureSocket();
	void closeSocket();

protected:
	void write(const std::string& s) override;
	std::string read() override;

	bool connectSocket();
	bool disconnectSocket();

public:
	/**
	 * @brief Create TCP/IP connector to trackPlatform
	 * @warning Only one object of that class in one moment of time is supported
	 *
	 * @param ip IP of trackPlatform Wi-Fi module
	 * @warning Supports only single IP, no masks
	 * @param port Port of TCP/IP server on trackPlatform
	 */
	TCPIP_Connector(const std::string& ip, uint16_t port);
	virtual ~TCPIP_Connector();

	bool isConnected() override;
	void connect() override;
	void disconnect() override;
};

#endif /* _TCPIP_CONNECTOR_H_ */
