#include "Constants.h"
#include "connectors/WiFi.h"
#include "connectors/ConnectingDevice.h"
#include "connectors/Bluetooth.h"
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
		}
		else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
		}
	}
}

void loop()
{	
	delay(100); //for sending commands from mobile 
	String command = device->read();
	controller.handle(device, command);
}
