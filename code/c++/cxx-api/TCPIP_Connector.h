#ifndef _TCPIP_CONNECTOR_H_
#define _TCPIP_CONNECTOR_H_

#include "TrackPlatform_BasicConnector.h"

class TCPIP_Connector : public TrackPlatform_BasicConnector
{
	std::string ip;
	uint16_t port;

protected:
	void write(const std::string& s) override;
	std::string read() override;
public:
	TCPIP_Connector(const std::string& ip, uint16_t port);

	bool isConnected() override;
};

#endif
