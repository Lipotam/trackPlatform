#include "Constants.h"
#include "connectors/WiFi.h"
#include "connectors/ConnectingDevice.h"
#include "connectors/Bluetooth.h"
#include "CommandsController.h"
#include "connectors/USB.h"
#include "connectors/DebugSerial.h"

Constants constants;
Bluetooth bluetooth(constants.bluetooth_RX, constants.bluetooth_TX, constants.bluetooth_serial_speed);
WiFi wifi(constants.wifi_RX, constants.wifi_TX, constants.wifi_serial_speed);
USB usb;
ConnectingDevice *device;
CommandsController controller;
Stream* debugSerial = DebugSerial::getSerial();

bool connected = false;

void setup()
{
	debugSerial->println("Arduino was started");
	while (!connected) {
		if (bluetooth.isActive()) {
			connected = true;
			device = &bluetooth;
			debugSerial->println("Bluetooth");
		}
		else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
			debugSerial->println("Wifi");
		}
		else if (usb.isActive()) {
			connected = true;
			device = &usb;
			debugSerial->println("USB");
		}
	}
}

void loop()
{
	delay(100); //for sending commands from mobile 
	String command = device->read();
	controller.handle(device, command);

	//debug
	for (int i = 0; i < command.length(); ++i)
	{
		debugSerial->printf("%02X ", command[i]);
	}
	if (command.length() > 0)
	{
		debugSerial->println("");
	}
}
