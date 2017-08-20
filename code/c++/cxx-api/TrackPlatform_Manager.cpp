#include "TrackPlatform_Manager.h"
#include "SerialConnector.h"
#include "TCPIP_Connector.h"

TrackPlatform_BasicConnector* TrackPlatform_Manager::createConnectorByMode(ConnectionModes mode, const CommunicationInfoStruct& info)
{
	TrackPlatform_BasicConnector* res;

	//TODO: add more modes
	switch (mode)
	{
	case USB:
	case bluetooth:
		res = new SerialConnector(info.SerialInfo.rxPort, info.SerialInfo.txPort, info.SerialInfo.baudrate);
		break;
	case WiFi: 
		res = new TCPIP_Connector(info.TCPIPInfo.ip, info.TCPIPInfo.port);
		break;
	default:
		res = nullptr;
		break;
	}
	
	return res;
}

TrackPlatform_Manager::TrackPlatform_Manager(ConnectionModes mode, const CommunicationInfoStruct& info) : 
	TrackPlatform_BasicManagement(createConnectorByMode(mode, info))
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
