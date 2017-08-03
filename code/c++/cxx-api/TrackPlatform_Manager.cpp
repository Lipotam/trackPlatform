#include "TrackPlatform_Manager.h"
#include "SerialConnector.h"

TrackPlatform_BasicConnector* TrackPlatform_Manager::createConnectorByMode(ConnectionModes mode, const std::string& rx, const std::string& tx, uint32_t baudRate)
{
	TrackPlatform_BasicConnector* res;

	//TODO: write
	switch (mode)
	{
	case USB:
		res = new SerialConnector(rx, tx, baudRate);
		break;
	case bluetooth:
		res = new SerialConnector(rx, tx, baudRate);
		break;
	default:
		res = nullptr;
		break;
	}
	
	return res;
}

TrackPlatform_Manager::TrackPlatform_Manager(ConnectionModes mode, const std::string& rx, const std::string& tx, uint32_t baudRate) : 
	TrackPlatform_BasicManagement(createConnectorByMode(mode, rx, tx, baudRate))
{
}

TrackPlatform_Manager::~TrackPlatform_Manager()
{
	TrackPlatform_BasicConnector* connector = getConnector();
	if (connector)
	{
		delete connector;
	}
}
