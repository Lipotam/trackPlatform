#include "Constants.h"
#include "ConnectingDevice.h"
#include "Bluetooth.h"
#include "WiFi.h"
#include "SoftwareSerial.h"
#include "CommandsController.h"


Constants constants;
Bluetooth bluetooth(constants.bluetooth_RX, constants.bluetooth_TX, constants.bluetooth_serial_speed);
WiFi wifi(constants.wifi_RX, constants.wifi_TX, constants.wifi_serial_speed);
ConnectingDevice *device;
CommandsController controller;

bool connected = false;


void setup()
{
	while (!connected) {
		if (bluetooth.isActive()) {
			connected = true;
			device = &bluetooth;
			delete &wifi;
		}
		else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
			delete &bluetooth;
		}
	}
}


void loop()
{	
	controller.handle(device, device->read());
}
