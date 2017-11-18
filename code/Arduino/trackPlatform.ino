#include "connectors/ConnectingDevice.h"
#include "management/CommandsController.h"
#include "connectors/DebugSerial.h"
#include "peripheral/ConnectionController.h"

Constants constants;
ConnectionController* connector;
CommandsController* controller = nullptr;

void setup()
{
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
