#include "ConnectorEnum.h"
#include "../peripheral/display/DisplayManager.h"
#include "Bluetooth.h"

bool Bluetooth::is_inited_ = false;

Bluetooth::Bluetooth(unsigned long speed) : IConnector(&Serial3)
{
	if (!is_inited_)
	{
		is_inited_ = true;
		Serial3.begin(speed);
		DisplayManager::get_manager()->init_connector(ConnectorEnum::bluetooth_connector);
	}
}

Bluetooth::~Bluetooth()
{
}
