#include "connection/ConnectingDevice.h"
#include "management/CommandsController.h"
#include "connection/DebugSerial.h"
#include "peripheral/ConnectionController.h"

ConnectionController* connector;
CommandsController* controller = nullptr;

void setup()
{
	DEBUG_PRINTLN("Trying to start Arduino");

	controller = new CommandsController();
	connector = new ConnectionController();

	DEBUG_PRINTLN("Arduino was started");

	connector->waitForConnection();
}

void loop()
{
	auto command = connector->getCommand();
	if (command.length() >= 2)
	{
		controller->handle(connector->getDevice(), command);
	}
	else
	{
		DEBUG_PRINTLN("Command is short");
	}
}
