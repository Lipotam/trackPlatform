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
USB* usb;
ConnectingDevice *device = nullptr;
CommandsController* controller;

void setup()
{
#ifdef DIOD_DEBUG
	diodInit();
#endif /* DIOD_DEBUG */

	DEBUG_PRINTLN("Arduino was started");

	usb = new USB();
	controller = new CommandsController();

	bool connected = false;
	while (!connected) {
		if (bluetooth.isActive()) {
			connected = true;
			device = &bluetooth;
			DEBUG_PRINTLN("Bluetooth");
		}
		else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
			DEBUG_PRINTLN("Wifi");
		}
		else if (usb->isActive()) {
			connected = true;
			device = usb;
			DEBUG_PRINTLN("USB");
		}
	}
}

void loop()
{
	while (device->isActive())
	{
		String command = device->read();

		//debug 
		DEBUG_PRINT("Command: ");
		DEBUG_PRINTLNHEX(command);

		controller->handle(device, command);
	}
	delay(1); //for sending commands from mobile (not required)
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
