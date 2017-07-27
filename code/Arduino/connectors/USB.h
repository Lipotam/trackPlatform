#pragma once

#include <HardwareSerial.h>
#include "ConnectingDevice.h"

class USB : public ConnectingDevice
{
public:
	USB();
};
