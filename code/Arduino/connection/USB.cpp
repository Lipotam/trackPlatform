#include "ConnectorEnum.h"
#include "../peripheral/display/DisplayManager.h"
#include "USB.h"

bool USB::is_inited_ = false;

USB::USB(unsigned long speed) : IConnector(&Serial)
{
	if (!is_inited_)
	{
		is_inited_ = true;
		Serial.begin(speed);
		DisplayManager::get_manager()->init_connector(ConnectorEnum::usb_connector);
	}
}

USB::~USB()
{
}
