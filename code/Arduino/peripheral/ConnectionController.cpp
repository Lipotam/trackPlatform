#include "../config/Constants.h"
#include "../config/CommandsEnum.h"
#include "../connection/DebugSerial.h"
#include "../utils/Timer.h"

#include "ConnectionController.h"

const char ConnectionController::connectCommand[] = { communicationControllerID, startCommunicationCommand, 0 };
const char ConnectionController::disconnectCommand[] = { communicationControllerID, stopCommunicationCommand, 0 };
const char ConnectionController::refreshCommand[] = { communicationControllerID, refreshConnectionCommunicationCommand, 0 };

ConnectionController::ConnectionController() : connectedAPIversion(startBasicAPI)
{
	usb = new USB(Constants::usb_serial_speed);
	wifi = new WiFi(Constants::wifi_serial_speed);
	bluetooth = new Bluetooth(Constants::bluetooth_serial_speed);
}

ConnectionController::~ConnectionController()
{
	if (usb)
	{
		delete usb;
	}
	if (wifi)
	{
		delete wifi;
	}
	if (bluetooth)
	{
		delete bluetooth;
	}
}

void ConnectionController::waitForConnection()
{
	DEBUG_PRINTLN("Arduino tries to found a manager");

	while (!isConnected) {
		//waiting some info
		while (!bluetooth->is_need_to_read_message() && !usb->is_need_to_read_message() && !wifi->is_need_to_read_message())
		{
			delay(1);
		}

		DEBUG_PRINTLN("Info was found");

		//reading info
		if (bluetooth->is_need_to_read_message()) {
			device = bluetooth;
			DEBUG_PRINTLN("Bluetooth sends something");
		}
		else if (wifi->is_need_to_read_message()) {
			device = wifi;
			DEBUG_PRINTLN("Wifi sends something");
		}
		else if (usb->is_need_to_read_message()) {
			device = usb;
			DEBUG_PRINTLN("USB sends something");
		}

		String readInfo = device->read_message();

		//check first part of command (if that command is connection command)
		if (readInfo.length() < sizeof (connectCommand) || (readInfo.substring(0, sizeof(connectCommand) - 1) != connectCommand))
		{
			DEBUG_PRINT("Bad info: ");
			DEBUG_PRINTLNHEX(readInfo);
			continue;
		}

		readInfo = readInfo.substring(sizeof(connectCommand) - 1);

		//check API version length
		if (readInfo.length() != 1)
		{
			DEBUG_PRINTF("Bad API version. Version was very long: %d symbols\n", readInfo.length());
			continue;
		}

		//check API version
		connectedAPIversion = static_cast<StartCommands>(readInfo[0]);
		if (connectedAPIversion > highestAPI || connectedAPIversion < lowestAPI)
		{
			DEBUG_PRINTF("Bad API version. Was %d, required in [%d, %d] interval\n", connectedAPIversion, lowestAPI, highestAPI);
			continue;
		}		
		DEBUG_PRINTF("Connected API version: %d\n", connectedAPIversion);
		isConnected = true;
	}

	//API v1 & v2 compatibility
	if (connectedAPIversion >= APIWithAnswer)
	{
		device->write_answer("OK");
	}
	DEBUG_PRINTLN("Arduino found a manager");
}

IConnector* ConnectionController::getDevice() const
{
	return device;
}

bool ConnectionController::waitForCommandOnDevice(Timer* timer)
{
	//compatibility with API v1 & v2
	if (connectedAPIversion >= APIWithAutoDiconnect)
	{
		while (!device->is_need_to_read_message() && timer->getState() != timerState_finished)
		{
			delay(1);
		}

		if (timer->getState() == timerState_finished)
		{
			return false;
		}
	}
	else
	{
		while (!device->is_need_to_read_message())
		{
			delay(1);
		}
	}

	return true;
}

String ConnectionController::getCommand()
{
	if (!isConnected)
	{
		return "";
	}

	String command;
	Timer timer(Constants::wait_command_time_in_ms);
	timer.startOrResume();
	do
	{
		if (!waitForCommandOnDevice(&timer))
		{
			isConnected = false;
			waitForConnection();
			timer.reset();
			continue;
		}

		command = device->read_message();

		//API v1 & v2 compatibility
		if (connectedAPIversion >= APIWithAnswer)
		{
			device->write_answer("OK");
		}

		//debug
		DEBUG_PRINT("Command: ");
		DEBUG_PRINTLNHEX(command);

		if (command == disconnectCommand)
		{
			isConnected = false;
			waitForConnection();
			timer.reset();
			continue;
		}

		if (connectedAPIversion >= APIWithAutoDiconnect && command == refreshCommand)
		{
			timer.reset();
			continue;
		}

		break;
	} while (true);
	return command;
}
