#include "CommandsEnum.h"
#include "TrackPlatform_BasicConnector.h"

void TrackPlatform_BasicConnector::sendStartCommand()
{
    std::string command = std::string() + (char)communicationControllerID + (char)startCommunicationCommand + (char)startBasicAPI;
    this->write(command);
}
void TrackPlatform_BasicConnector::sendStopCommand()
{
    std::string command = std::string() + (char)communicationControllerID + (char)stopCommunicationCommand;
	this->write(command);
}

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	rxLocation(rx), txLocation(tx), baudRate(baudRate)
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}
