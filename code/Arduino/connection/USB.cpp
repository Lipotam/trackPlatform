#include "USB.h"

bool USB::isInited = false;

USB::USB(unsigned long speed) : IConnector(&Serial)
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
