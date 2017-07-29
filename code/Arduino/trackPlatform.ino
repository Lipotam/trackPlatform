#include "Constants.h"
#include "connectors/WiFi.h"
#include "connectors/ConnectingDevice.h"
#include "connectors/Bluetooth.h"
#include "CommandsController.h"
#include "connectors/USB.h"
#include "connectors/DebugSerial.h"

#define DIOD_DEBUG

#ifdef DIOD_DEBUG
void diodInit();
void on43();
void off43();
void on45();
void off45();

#endif /* DIOD_DEBUG */

Constants constants;
Bluetooth bluetooth(constants.bluetooth_RX, constants.bluetooth_TX, constants.bluetooth_serial_speed);
WiFi wifi(constants.wifi_RX, constants.wifi_TX, constants.wifi_serial_speed);
USB usb;
ConnectingDevice *device = nullptr;
CommandsController controller;
Stream* debugSerial = DebugSerial::getSerial();

bool connected = false;

void setup()
{
#ifdef DIOD_DEBUG
	diodInit();
#endif /* DIOD_DEBUG */

	Serial.begin(Constants::usb_serial_speed);

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

#ifdef DIOD_DEBUG

void diodInit()
{
	pinMode(43, OUTPUT);
	pinMode(45, OUTPUT);
}

void on43()
{
	digitalWrite(43, HIGH);
}

void off43()
{
	digitalWrite(43, LOW);
}

void on45()
{
	digitalWrite(45, HIGH);
}

void off45()
{
	digitalWrite(45, LOW);
}

#endif /* DIOD_DEBUG */
