#include "ConnectingDevice.h"
#include "SoftwareSerial.h"

ConnectingDevice::ConnectingDevice(int rx, int tx, int speed)
{
	 device = new SoftwareSerial(rx, tx);
	 device->begin(speed);
	 device->listen();	 
}

void ConnectingDevice::send(String data) 
{
	this->device->println(data);
}

bool ConnectingDevice::isActive() 
{
	(*this).send("lol");
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
