#ifndef _BLUETOOTH_CONNECTOR_H_
#define _BLUETOOTH_CONNECTOR_H_

#include "serial/serial.h"
#include "StreamConnector.h"

class SerialConnector : public StreamConnector
{
	static const size_t messageMaxSize = 65535;
	static const size_t timeoutInMs = 1500;
	
	std::string rxLocation;
	std::string txLocation;
	uint32_t baudRate;

	serial::Serial* readPort;
	serial::Serial* writePort;

protected:
	void write(const std::string& s) override;

	std::string streamRead(uint64_t size) override;
	uint64_t streamAvailable() override;

public:
	SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate);
	~SerialConnector() override;
	bool isConnected() override;
	void connect() override;
	void disconnect() override;
};

#endif /* _BLUETOOTH_CONNECTOR_H_ */
