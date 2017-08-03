#include "Constants.h"
#include "connectors/WiFi.h"
#include "connectors/ConnectingDevice.h"
#include "connectors/Bluetooth.h"
#include "CommandsController.h"
#include "connectors/USB.h"
#include "connectors/DebugSerial.h"
#include "CommandsEnum.h"

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
DebugSerial debugSerial;

char connectCommand[] = { communicationControllerID, startCommunicationCommand, startBasicAPI };
char disconnectCommand[] = {communicationControllerID, stopCommunicationCommand };

bool connected = false;

void selectDevice()
{
	debugSerial.println("Arduino tries to found a manager");
	while (!connected) {
		if (bluetooth.isActive() && bluetooth.read() == connectCommand) {
			connected = true;
			device = &bluetooth;
			debugSerial.println("Bluetooth");
		}
		else if (wifi.isActive() && wifi.read() == connectCommand) {
			connected = true;
			device = &wifi;
			debugSerial.println("Wifi");
		}
		else if (usb.isActive() && usb.read() == connectCommand) {
			connected = true;
			device = &usb;
			debugSerial.println("USB");
		}
	}
	debugSerial.println("Arduino found a manager");
}

void setup()
{
#ifdef DIOD_DEBUG
	diodInit();
#endif /* DIOD_DEBUG */

	Serial.begin(Constants::usb_serial_speed);

	debugSerial.println("Arduino was started");

	selectDevice();
}

void loop()
{
	while (device->isActive())
	{
		String command = device->read();

		//debug
		debugSerial.print("Command: ");
		debugSerial.printlnHex(command);

		if (command == disconnectCommand)
		{
			selectDevice();
		}
		else
		{
			controller.handle(device, command);
		}
	}
	delay(100); //for sending commands from mobile (not required)
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
