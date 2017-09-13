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

std::string SerialConnector::read()
{
	return readPort->read(messageMaxSize);
}

bool SerialConnector::isConnected()
{
	return (TrackPlatform_BasicConnector::isConnected() && readPort->isOpen() && writePort->isOpen());
}

std::string SerialConnector::readOneAnswer()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}

	auto text = readPort->readline(messageMaxSize, std::string(1, stopSymbol));
	if (!text.length() || text.back() != stopSymbol)
	{
		throw CorruptedAnswerException();
	}
	
	text.pop_back();
	return text;
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
