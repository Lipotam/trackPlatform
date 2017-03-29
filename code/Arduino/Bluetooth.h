#pragma once
#include "ConnectingDevice.h"

class Bluetooth : public ConnectingDevice
{
public:
	Bluetooth(int rx, int tx, int speed);
	~Bluetooth();
};

