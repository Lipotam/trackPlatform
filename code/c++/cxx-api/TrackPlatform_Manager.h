#ifndef _TRACKPLATFORM_MANAGER_H_
#define _TRACKPLATFORM_MANAGER_H_

#include "TrackPlatform_BasicManagement.h"
#include "ConnectionModes.h"

class TrackPlatform_Manager : public TrackPlatform_BasicManagement
{
	static TrackPlatform_BasicConnector* createConnectorByMode(ConnectionModes mode, const std::string& rx, const std::string& tx, uint32_t baudRate);

public:
	TrackPlatform_Manager(ConnectionModes mode, const std::string& rx, const std::string& tx, uint32_t baudRate);
	~TrackPlatform_Manager();
};

#endif /* _TRACKPLATFORM_MANAGER_H_ */
