#include "../Constants.h"
#include "Bluetooth.h"

bool Bluetooth::isInited = false;

Bluetooth::Bluetooth() : ConnectingDevice(&Serial3)
{
	if (!isInited)
	{
		isInited = true;
		Serial3.begin(Constants::bluetooth_serial_speed);
	}
}

Bluetooth::~Bluetooth()
{
}
