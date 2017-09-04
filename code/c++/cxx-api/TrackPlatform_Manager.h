#ifndef _TRACKPLATFORM_MANAGER_H_
#define _TRACKPLATFORM_MANAGER_H_

#include "TrackPlatform_BasicManagement.h"
#include "ConnectionModes.h"
#include "CommunicationInfoStruct.h"
#include "AutoConnector.h"

class TrackPlatform_Manager : public TrackPlatform_BasicManagement
{
	static TrackPlatform_BasicConnector* createConnectorByMode(ConnectionModes mode, const CommunicationInfoStruct& info);
	AutoConnector* pAutoConnector;

public:
	TrackPlatform_Manager(ConnectionModes mode, const CommunicationInfoStruct& info);
	~TrackPlatform_Manager();

	void startAutoConnection();
	void stopAutoConnection();
};

#endif /* _TRACKPLATFORM_MANAGER_H_ */
