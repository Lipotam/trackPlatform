#pragma once
#include "ConnectingDevice.h"

class WiFi : public ConnectingDevice
{
public:
	WiFi(int rx, int tx, int speed);
	~WiFi();
};

