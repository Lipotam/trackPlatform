#ifndef _TCPIP_CONNECTOR_H_
#define _TCPIP_CONNECTOR_H_

#if !(defined(__linux__) || defined(__unix__))

#error This header file must be used only on linux or unix platforms

#else /* !(defined(__linux__) || defined(__unix__)) */

#define SOCKET 						int
#define INVALID_SOCKET 				(-1)

#include "TrackPlatform_BasicConnector.h"

class TCPIP_Connector : public TrackPlatform_BasicConnector
{
	std::string ip;
	uint16_t port;

	static const uint16_t onePacketMaxSize = 512;
	static const int32_t microsecondsToWaitAnswer = 100000;

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

#endif /* !(defined(__linux__) || defined(__unix__)) */
#endif /* _TCPIP_CONNECTOR_H_ */
