#include "ConnectingDevice.h"
#include "SoftwareSerial.h"

ConnectingDevice::ConnectingDevice(Stream* ptr) : device(ptr)
{
}

ConnectingDevice::ConnectingDevice(int rx, int tx, int speed)
{
	SoftwareSerial* serialPtr = new SoftwareSerial(rx, tx);
	device = serialPtr;
	serialPtr->begin(speed);
	serialPtr->listen();
}

void ConnectingDevice::send(String data) 
{
	this->device->println(data);
}

bool ConnectingDevice::isActive() 
{
	if ((*device).available()) {
		return true;
	}
	return false;
}

String ConnectingDevice::read()
{
	String command = "";

	while ((*device).available()) {
		char code = (*device).read();
		command += code;
	}
	return command;
}


ConnectingDevice::~ConnectingDevice()
{
}
