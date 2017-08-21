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
Bluetooth* bluetooth = nullptr;
WiFi* wifi = nullptr;
USB* usb = nullptr;
ConnectingDevice *device = nullptr;
CommandsController* controller = nullptr;

char connectCommand[] = { communicationControllerID, startCommunicationCommand, startBasicAPI, 0 };
char disconnectCommand[] = { communicationControllerID, stopCommunicationCommand, 0 };

void selectDevice()
{
	bool connected = false;
	DEBUG_PRINTLN("Arduino tries to found a manager");
	while (!connected) {
		if (bluetooth->isActive() && bluetooth->read() == connectCommand) {
			connected = true;
			device = bluetooth;
			DEBUG_PRINTLN("Bluetooth");
		}
		else if (wifi->isActive() && wifi->read() == connectCommand) {
			connected = true;
			device = wifi;
			DEBUG_PRINTLN("Wifi");
		}
		else if (usb->isActive() && usb->read() == connectCommand) {
			connected = true;
			device = usb;
			DEBUG_PRINTLN("USB");
		}
	}

	device->send("OK");
	DEBUG_PRINTLN("Arduino found a manager");
}

void setup()
{
#ifdef DIOD_DEBUG
	diodInit();
#endif /* DIOD_DEBUG */

	usb = new USB(Constants::usb_serial_speed);
    wifi = new WiFi(Constants::wifi_serial_speed);
	bluetooth = new Bluetooth(Constants::bluetooth_serial_speed);
	controller = new CommandsController();

	DEBUG_PRINTLN("Arduino was started");

	selectDevice();
}

void loop()
{
	while (device->isActive())
	{
		String command = device->read();

		//debug
		DEBUG_PRINT("Command: ");
		DEBUG_PRINTLNHEX(command);

		if (command == disconnectCommand)
		{
			selectDevice();
		}
		else
		{
			controller->handle(device, command);
		}
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
