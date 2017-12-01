#include "SerialConnector.h"
#include "trackPlatformAllExceptions.h"

extern "C" {
#include "checksum.h"
}

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
	if (buffer.empty() || (buffer[0] + crc_length + sizeof(buffer[0])) > buffer.length())
	{
		buffer += readPort->read(messageMaxSize);
	}

	uint8_t len = buffer[0];
	if ((len + crc_length + sizeof(buffer[0])) > buffer.length())
	{
		throw TimeoutException();
	}

	const uint16_t substring_len = sizeof(len) + len + crc_length;
	std::string answer = buffer.substr(0, substring_len);
	buffer.erase(0, substring_len);

	return answer;
}

std::string SerialConnector::generatePackage(const std::string& command)
{
	std::string package = static_cast<char>(command.length()) + command;
	uint16_t crc = crc_modbus(reinterpret_cast<const unsigned char*>(package.c_str()), package.length());
	for (size_t i = 0; i < crc_length; ++i)
	{
		package.push_back((reinterpret_cast<char *>(&crc))[i]);
	}
	return package;
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
