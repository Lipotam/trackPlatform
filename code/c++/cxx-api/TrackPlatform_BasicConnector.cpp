#include <chrono>
#include <thread>

#include "Logger.h"
#include "trackPlatformAllExceptions.h"
#include "CommandsEnum.h"

#include "TrackPlatform_BasicConnector.h"

const std::string TrackPlatform_BasicConnector::connectedAnswer = "OK";

void TrackPlatform_BasicConnector::sendStartCommand()
{
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(startCommunicationCommand) + static_cast<char>(startBasicAPI);
	isConnectedToArduino = true;
	for (auto i = 0; i < timesToAutoreconnect; ++i)
	{
		sendOneCommand(command);
		if (readOneAnswer() == connectedAnswer)
		{
			return;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(timeoutToNextConnectInMs));
	}

	isConnectedToArduino = false;
	throw CannotConnectToArduinoException();
}
void TrackPlatform_BasicConnector::sendStopCommand()
{
	if (!isConnected())
	{
		throw NoConnectionException();
	}
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(stopCommunicationCommand);
	sendOneCommand(command);
	isConnectedToArduino = false;
}

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector() 
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
	write(s + stopSymbol);
	Logger::log("Send: " + s + stopSymbol);
}

bool TrackPlatform_BasicConnector::isConnected()
{
	return isConnectedToArduino;
}
