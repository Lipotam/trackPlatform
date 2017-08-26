#include "../Constants.h"
#include "../CommandsEnum.h"
#include "../connectors/DebugSerial.h"

#include "ConnectionController.h"

const char ConnectionController::connectCommand[] = { communicationControllerID, startCommunicationCommand, startBasicAPI, 0 };
const char ConnectionController::disconnectCommand[] = { communicationControllerID, stopCommunicationCommand, 0 };

ConnectionController::ConnectionController()
{
	usb = new USB(Constants::usb_serial_speed);
	wifi = new WiFi(Constants::wifi_serial_speed);
	bluetooth = new Bluetooth(Constants::bluetooth_serial_speed);
}

void ConnectionController::waitForConnection()
{
	DEBUG_PRINTLN("Arduino tries to found a manager");
	while (!isConnected) {
		if (bluetooth->isActive() && bluetooth->read() == connectCommand) {
			isConnected = true;
			device = bluetooth;
			DEBUG_PRINTLN("Bluetooth");
		}
		else if (wifi->isActive()) {
		isConnected = true;
		device = wifi;
		DEBUG_PRINTLN("Wifi");
		}
		else if (usb->isActive()) {
			isConnected = true;
			device = usb;
			DEBUG_PRINTLN("USB");
		}
	}

	device->send("OK");
	DEBUG_PRINTLN("Arduino found a manager");
}

ConnectingDevice* ConnectionController::getDevice() const
{
	return device;
}

String ConnectionController::getCommand()
{
	if (!isConnected)
	{
		return "";
	}

	String command;
	do
	{
		while (!device->isActive())
		{
			delay(1);
		}

		command = device->read();

		//debug
		DEBUG_PRINT("Command: ");
		DEBUG_PRINTLNHEX(command);

		if (command != disconnectCommand)
		{
			break;
		}

		isConnected = false;
		waitForConnection();
	} while (true);
	return command;
}
