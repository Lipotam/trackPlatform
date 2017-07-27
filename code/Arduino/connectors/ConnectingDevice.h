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
	bool isActive();
	String read();
	void send(String data);
	virtual ~ConnectingDevice();
};

