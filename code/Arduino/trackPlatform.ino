#include "connectors/ConnectingDevice.h"
#include "CommandsController.h"
#include "connectors/DebugSerial.h"
#include "peripheral/ConnectionController.h"

#define DIOD_DEBUG

#ifdef DIOD_DEBUG

void diodInit();
void on43();
void off43();
void on45();
void off45();

#endif /* DIOD_DEBUG */

Constants constants;
ConnectionController* connector;
CommandsController* controller = nullptr;

void setup()
{
#ifdef DIOD_DEBUG
	diodInit();
#endif /* DIOD_DEBUG */

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
