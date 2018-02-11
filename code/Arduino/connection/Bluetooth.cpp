#include "Bluetooth.h"

bool Bluetooth::is_inited_ = false;

#define MODULE_SERIAL Serial2

Bluetooth::Bluetooth(unsigned long speed) : IConnector(&MODULE_SERIAL)
{
	if (!is_inited_)
	{
		is_inited_ = true;
		MODULE_SERIAL.begin(speed);
	}
}

Bluetooth::~Bluetooth()
{
}
