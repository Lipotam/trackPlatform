#include "SerialConnector.h"

void SerialConnector::write(const std::string& s)
{
	writePort->write(s);
	writePort->flush();
}

SerialConnector::SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	rxLocation(rx), txLocation(tx), baudRate(baudRate), readPort(new serial::Serial(rx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs))),
	writePort((rx == tx) ? readPort : new serial::Serial(tx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs)))
{
}

SerialConnector::~SerialConnector()
{
	SerialConnector::disconnect();
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

void SerialConnector::connect()
{
	if (readPort && !readPort->isOpen())
	{
		readPort->open();
	}
	if (writePort && !writePort->isOpen())
	{
		writePort->open();
	}
}

void SerialConnector::disconnect()
{
	if (readPort && readPort->isOpen())
	{
		readPort->close();
	}
	if (writePort && writePort->isOpen())
	{
		writePort->close();
	}
}
