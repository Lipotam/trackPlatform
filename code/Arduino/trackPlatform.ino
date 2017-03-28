#include "Constants.h"
#include "ConnectingDevice.h"
#include "Bluetooth.h"
#include "WiFi.h"
#include "SoftwareSerial.h"
#include "CommandsController.h"

Bluetooth bluetooth;
WiFi wifi;
ConnectingDevice *device;
CommandsController controller;
Constants constants;
bool connected = false;


void setup()
{
}


void loop()
{	

	if (!connected) {
		if (bluetooth.isActive()) {
			connected = true;
			device = &bluetooth;
		} else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
		}
	}
	else {
		controller.handle(device, device->read());
	}
}
