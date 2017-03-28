#pragma once
#include <SoftwareSerial.h>

class ConnectingDevice
{
protected:
	SoftwareSerial *device;
public:
	ConnectingDevice(int, int);
	bool isActive();
	int read();
	void send(String data);
	virtual ~ConnectingDevice();
};

