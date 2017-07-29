#pragma once
#include <Arduino.h>
#include <Stream.h>

class ConnectingDevice
{
protected:
	explicit ConnectingDevice(Stream* ptr);

	Stream *device;
public:
	ConnectingDevice(int rx, int tx, int speed);
	virtual bool isActive();
	virtual String read();
	virtual void send(String data);
	virtual ~ConnectingDevice();
};

