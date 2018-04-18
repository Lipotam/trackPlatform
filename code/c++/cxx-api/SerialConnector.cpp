#include <algorithm>
#include "SerialConnector.h"
#include "trackPlatformAllExceptions.h"

void SerialConnector::write(const std::string& s)
{
	writePort->write(s);
	writePort->flush();
}

SerialConnector::SerialConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	rxLocation(rx), txLocation(tx), baudRate(baudRate), readPort(new serial::Serial(rx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs))),
	writePort((rx == tx) ? readPort : new serial::Serial(tx, baudRate, serial::Timeout::simpleTimeout(timeoutInMs)))
{
	sendStartCommand();
}

SerialConnector::~SerialConnector()
{
	sendStopCommand();

	SerialConnector::disconnect();
	if (readPort != writePort)
	{
		delete writePort;
	}
	delete readPort;
}

std::string SerialConnector::streamRead(uint64_t size)
{

	return readPort->read(size);
}

uint64_t SerialConnector::streamAvailable()
{
	return readPort->available();
}

bool SerialConnector::isConnected()
{
	return (TrackPlatform_BasicConnector::isConnected() && readPort->isOpen() && writePort->isOpen());
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
