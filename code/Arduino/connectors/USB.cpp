#include "../Constants.h"
#include "USB.h"

bool USB::isInited = false;

USB::USB() : ConnectingDevice(&Serial)
{
	if (!isInited)
	{
		isInited = true;
		Serial.begin(Constants::usb_serial_speed);
	}
}
