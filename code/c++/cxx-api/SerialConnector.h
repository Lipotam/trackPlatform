#ifndef _BLUETOOTH_CONNECTOR_H_
#define _BLUETOOTH_CONNECTOR_H_

#include "TrackPlatform_BasicConnector.h"
#include "serial/serial.h"

class SerialConnector : public TrackPlatform_BasicConnector
{
	static const size_t messageMaxSize = 65535;
	static const size_t timeoutInMs = 500;
	
	std::string rxLocation;
	std::string txLocation;
	uint32_t baudRate;

	serial::Serial* readPort;
	serial::Serial* writePort;

protected:
	void write(const std::string& s) override;
	std::string read() override;

public:
	SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate);
	~SerialConnector() override;
	bool isConnected() override;
	std::string readOneAnswer() override;
	void connect() override;
	void disconnect() override;
};

#endif /* _BLUETOOTH_CONNECTOR_H_ */
