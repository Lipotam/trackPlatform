/**
 * @(#) ConnectionSectorManager.h
 */

#ifndef CONNECTIONSECTORMANAGER_H_H
#define CONNECTIONSECTORMANAGER_H_H

#include "Adafruit.h"
#include "ToggleImageDisplaySector.h"
#include "../../connection/ConnectorEnum.h"

class ConnectionSectorManager
{

public:
	ConnectionSectorManager(Adafruit_GFX* gfx);
	void init_connector(const ConnectorEnum connector_index);
	void paint();
	void reset_all_connectors();
	void set_connector(const ConnectorEnum connector_index);

private:
	static const uint8_t kConnectorsNum = 3;

	ToggleImageDisplaySector* connectors_[kConnectorsNum]{ nullptr };
};

#endif
