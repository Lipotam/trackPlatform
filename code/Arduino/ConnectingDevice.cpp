#include "ConnectingDevice.h"



ConnectingDevice::ConnectingDevice(int rx, int tx)
{
	 device = new SoftwareSerial(rx, tx);
}

void ConnectingDevice::send(String data) 
{

}

bool ConnectingDevice::isActive() 
{
	
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
	connected = 0;
}
