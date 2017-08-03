#include "SerialConnector.h"

void SerialConnector::write(const std::string& s)
{
	writePort->write(s);
}

SerialConnector::SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	TrackPlatform_BasicConnector(rx, tx, baudRate), readPort(new serial::Serial(rx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs))), 
	writePort((rx == tx) ? readPort : new serial::Serial(tx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs)))
{
	sendStartCommand();
}

SerialConnector::~SerialConnector()
{
	sendStopCommand();

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

bool SerialConnector::isConnected()
{
	return (readPort->isOpen() && writePort->isOpen());
}

std::string SerialConnector::readOneAnswer()
{
	return readPort->readline(messageMaxSize, std::string(1, stopSymbol));
}
