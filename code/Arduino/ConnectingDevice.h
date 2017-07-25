#pragma once
#include <SoftwareSerial.h>
#include "Arduino.h"
class ConnectingDevice
{
protected:
	SoftwareSerial *device;

public:
	ConnectingDevice(int rx, int tx, int speed);
	bool isActive();
	String read();
	void send(String data);
	virtual ~ConnectingDevice();
};

