#include "CommandsEnum.h"
#include "TrackPlatform_BasicConnector.h"
#include "Logger.h"

void TrackPlatform_BasicConnector::sendStartCommand()
{
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(startCommunicationCommand) + static_cast<char>(startBasicAPI);
	sendOneCommand(command);
}
void TrackPlatform_BasicConnector::sendStopCommand()
{
    std::string command = std::string() + static_cast<char>(communicationControllerID) + static_cast<char>(stopCommunicationCommand);
	sendOneCommand(command);
}

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector() 
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}

std::string TrackPlatform_BasicConnector::readOneAnswer()
{
	return read();
}

void TrackPlatform_BasicConnector::sendOneCommand(const std::string& s)
{
	write(s + stopSymbol);
	Logger::log("Send: " + s + stopSymbol);
}
