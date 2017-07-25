#include "SerialConnector.h"

SerialConnector::SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	TrackPlatform_BasicConnector(rx, tx, baudRate), readPort(new serial::Serial(rx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs))), 
	writePort((rx == tx) ? readPort : new serial::Serial(tx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs)))
{
}

SerialConnector::~SerialConnector()
{
	if (readPort != writePort)
	{
		delete writePort;
	}
	delete readPort;
}

std::string SerialConnector::read()
{
	return readPort->read(messageMaxSize);
}

std::string SerialConnector::readAllAvailable()
{
	return (readPort->available() ? readPort->read(readPort->available()) : "");
}

void SerialConnector::write(const std::string& s)
{
	writePort->write(s);
}

bool SerialConnector::isConnected()
{
	return (readPort->isOpen() && writePort->isOpen());
}
