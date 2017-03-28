#pragma once
#include <SoftwareSerial.h>
#include "Constants.h"

class ConnectingDevice
{
protected:
	SoftwareSerial *device;
	Constants constants;

public:
	ConnectingDevice(int, int, int);
	bool isActive();
	int read();
	void send(String data);
	virtual ~ConnectingDevice();
};

