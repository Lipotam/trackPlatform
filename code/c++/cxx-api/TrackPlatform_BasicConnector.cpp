#include <chrono>
#include <thread>

#include "Logger.h"
#include "trackPlatformAllExceptions.h"
#include "CommandsEnum.h"

#include "TrackPlatform_BasicConnector.h"

extern "C" {
#include "checksum.h"
}

const char TrackPlatform_BasicConnector::stopSymbol;
const uint8_t TrackPlatform_BasicConnector::timesToAutoreconnect;
const uint32_t TrackPlatform_BasicConnector::timeoutToNextConnectInMs;
const std::string TrackPlatform_BasicConnector::correctAnswer = "OK";

std::string TrackPlatform_BasicConnector::generatePackage(const std::string& command)
{
	std::string package = static_cast<char>(command.length()) + command;
	uint16_t crc = crc_modbus(reinterpret_cast<const unsigned char*>(package.c_str()), package.length());
	for (size_t i = 0; i < sizeof(crc); ++i)
	{
		package.push_back((reinterpret_cast<char *>(&crc))[i]);
	}
	return package;
}

void TrackPlatform_BasicConnector::sendStartCommand()
{
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(startCommunicationCommand) + static_cast<char>(APIWithAutoDiconnect);
	isConnectedToArduino = true;
	sendOneCommand(command);
	autoConnector->start();
}
void TrackPlatform_BasicConnector::sendStopCommand()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
	autoConnector->stop();
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(stopCommunicationCommand);
	sendOneCommand(command);
	isConnectedToArduino = false;
}

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector() : 
	autoConnector(new AutoConnector([this]()
	{
		this->sendOneCommand(std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(refreshConnectionCommunicationCommand));
	}, timeoutToAutoreconnectInMs))
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}

std::string TrackPlatform_BasicConnector::readOneAnswer()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
	return read();
}

void TrackPlatform_BasicConnector::sendOneCommand(const std::string& s)
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
	const std::string package = generatePackage(s);
	Logger::log("Send: " + package + stopSymbol);
	for (auto i = 0; i < timesToAutoreconnect; ++i)
	{
		Logger::log("Trying to send command. Attempt " + std::to_string(i + 1));
		write(package);
		try {
			if (readOneAnswer() == correctAnswer)
			{
				Logger::log("Sending successfully");
				return;
			}
		}
		catch (CorruptedAnswerException&)
		{
			//All is good, module not answered, try again
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(timeoutToNextConnectInMs));
	}

	isConnectedToArduino = false;
	Logger::log("Cannot connect to arduino");
	throw CannotConnectToArduinoException();
}

bool TrackPlatform_BasicConnector::isConnected()
{
	return isConnectedToArduino;
}
