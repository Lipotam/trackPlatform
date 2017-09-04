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
	std::function<void()> callback = [this]() { this->refreshConnection(); };
	pAutoConnector = new AutoConnector(callback);
	pAutoConnector->start();
}

TrackPlatform_Manager::~TrackPlatform_Manager()
{
	TrackPlatform_BasicConnector* connector = getConnector();
	if (connector)
	{
		delete connector;
	}
	if (pAutoConnector) delete pAutoConnector;
}

void TrackPlatform_Manager::startAutoConnection() {
	pAutoConnector->start();
}
void TrackPlatform_Manager::stopAutoConnection() {
	pAutoConnector->stop();
}