#include "Constants.h"
#include "ConnectingDevice.h"
#include "Bluetooth.h"
#include "WiFi.h"
#include "SoftwareSerial.h"

Bluetooth bluetooth;
WiFi wifi;
ConnectingDevice *device;
int connected = false;


void setup()
{

}


void loop()
{	
	if (!connected) {
		if (wifi.isActive()) { 
			connected = true;
			device = wifi;
		}
		else if (bluetooth.isActive()) {
			connected = true;
			device = bluetooth;
		}
	}
	else {
		commandsController.handle(device->read());
	}



























	if (BTserial.available() > 0) {
		while (BTserial.available() > 0) {
			char code = BTserial.read();
			inString += code;
		}

		int com = inString.toInt();
		
		/* should be constants in case from Commands.h, but get error! */
		
		switch (com)
		{
		case 0:
			BTserial.println("TEST: OK");
			break;
		case 1:
			BTserial.println("MOVING FORWARD");
			break;
		case 2:
			BTserial.println("TURNING LEFT");
			break;
		case 3:
			BTserial.println("TURNING RIGHT");
			break;
		case 4:
			BTserial.println("MOVING BACK");
			break;
		default:
			break;
		}

		inString = "";
	}

}
