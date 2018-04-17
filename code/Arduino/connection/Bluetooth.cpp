#include "ConnectorEnum.h"
#include "../peripheral/display/DisplayManager.h"
#include "Bluetooth.h"

bool Bluetooth::is_inited_ = false;

#define MODULE_SERIAL Serial2

Bluetooth::Bluetooth(unsigned long speed) : IConnector(&MODULE_SERIAL)
{
	if (!is_inited_)
	{
		is_inited_ = true;
		MODULE_SERIAL.begin(speed);
		DisplayManager::get_manager()->init_connector(ConnectorEnum::bluetooth_connector);
	}
}

Bluetooth::~Bluetooth()
{
}
