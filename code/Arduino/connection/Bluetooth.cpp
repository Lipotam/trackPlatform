#include "Bluetooth.h"

bool Bluetooth::isInited = false;

Bluetooth::Bluetooth(unsigned long speed) : IConnector(&Serial3)
{
	if (!isInited)
	{
		isInited = true;
		Serial3.begin(speed);
	}
}

Bluetooth::~Bluetooth()
{
}
