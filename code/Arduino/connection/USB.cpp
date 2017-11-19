#include "USB.h"

bool USB::isInited = false;

USB::USB(unsigned long speed) : ConnectingDevice(&Serial)
{
	if (!isInited)
	{
		isInited = true;
		Serial.begin(speed);
	}
}

USB::~USB()
{
}
