#include <SoftwareSerial.h>

#include "../config/Constants.h"
#include "ConnectingDevice.h"

ConnectingDevice::ConnectingDevice(Stream* ptr) : device(ptr)
{
	device->setTimeout(Constants::commands_wait_time);
}

ConnectingDevice::ConnectingDevice(int rx, int tx, unsigned long speed)
{
	SoftwareSerial* serialPtr = new SoftwareSerial(rx, tx);
	serialPtr->begin(speed);
	serialPtr->listen();

	device = serialPtr;
	device->setTimeout(Constants::commands_wait_time);
}

void ConnectingDevice::send(String data)
{
	device->print(data + Constants::commands_stop_symbol);
}

bool ConnectingDevice::isActive()
{
	return device->available();
}

String ConnectingDevice::read()
{
	return device->readStringUntil(Constants::commands_stop_symbol);
}


ConnectingDevice::~ConnectingDevice()
{
}
