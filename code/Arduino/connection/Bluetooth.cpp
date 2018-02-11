#include "Bluetooth.h"

bool Bluetooth::is_inited_ = false;

Bluetooth::Bluetooth(unsigned long speed) : IConnector(&Serial2)
{
	if (!is_inited_)
	{
		is_inited_ = true;
		Serial3.begin(speed);
	}
}

Bluetooth::~Bluetooth()
{
}
