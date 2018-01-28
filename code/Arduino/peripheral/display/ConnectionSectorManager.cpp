/**
 * @(#) ConnectionSectorManager.cpp
 */

#include "../../config/Constants.h"
#include "../../connection/DebugSerial.h"
#include "ConnectionSectorManager.h"
void ConnectionSectorManager::init_connector(const ConnectorEnum connector_index)
{
	ToggleImageDisplaySector* connector = connectors_[connector_index];
	if(!connector)
	{
		DEBUG_PRINTF("Connector is not set. Index: %d, function: %s, line: %d\n", connector_index, __FUNCTION__, __LINE__);
		return;
	}
	connector->set_state(released);
}

void ConnectionSectorManager::paint()
{
	for(uint8_t i = 0; i < kConnectorsNum; ++i)
	{
		ToggleImageDisplaySector* connector = connectors_[i];
		if(connector->is_changed())
		{
			connector->paint();
		}
	}
}

ConnectionSectorManager::ConnectionSectorManager(Adafruit_GFX* gfx)
{
	connectors_[ConnectorEnum::usb_connector] = new ToggleImageDisplaySector(gfx, Constants::kUsbImageConfiguration, Constants::kUsbImage);
	connectors_[ConnectorEnum::bluetooth_connector] = new ToggleImageDisplaySector(gfx, Constants::kBluetoothImageConfiguration, Constants::kBluetoothImage);
	connectors_[ConnectorEnum::wifi_connector] = new ToggleImageDisplaySector(gfx, Constants::kWifiImageConfiguration, Constants::kWifiImage);
}

void ConnectionSectorManager::reset_all_connectors()
{
	for(uint8_t i = 0; i < kConnectorsNum; ++i)
	{
		connectors_[i]->set_state(released);
	}
}

void ConnectionSectorManager::set_connector(const ConnectorEnum connector_index)
{
	for(uint8_t i = 0; i < kConnectorsNum; ++i)
	{
		connectors_[i]->set_state((connector_index == i) ? pressed : released);
	}
}

