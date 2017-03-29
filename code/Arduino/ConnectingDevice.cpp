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
	if (this->device->available()) {
		return true;
	}
	return false;
}

int ConnectingDevice::read()
{
	String inString = "";

	while ((*device).available() > 0) {
		char code = (*device).read();
		inString += code;
	}
	return inString.toInt();
}


ConnectingDevice::~ConnectingDevice()
{
}
