#ifndef _TCPIP_CONNECTOR_H_
#define _TCPIP_CONNECTOR_H_

#ifndef _WIN32

#error This header file must be used only on Windows desktop platforms (win32) 

#else /* _WIN32 */

/* WinAPI include */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")

#include "TrackPlatform_BasicConnector.h"

class TCPIP_Connector : public TrackPlatform_BasicConnector
{
	std::string ip;
	uint16_t port;

	static const uint16_t onePacketMaxSize = 512;
	static const int32_t microsecondsToWaitAnswer = 100000;

	WSADATA wsaData;
	struct addrinfo *addressInfo = nullptr;
	SOCKET connectedSocket = INVALID_SOCKET;

	bool isConnected_private = false;

	void configureSocket();
	void closeSocket();

protected:
	void write(const std::string& s) override;
	std::string read() override;

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

#endif /* _WIN32 */
#endif /* _TCPIP_CONNECTOR_H_ */
