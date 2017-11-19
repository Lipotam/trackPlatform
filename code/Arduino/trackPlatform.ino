#include "connection/DebugSerial.h"
#include "management/MainManager.h"
#include "connection/ConnectionManager.h"

//ConnectionController* connector;
//CommandsController* controller = nullptr;

void setup()
{
	DEBUG_PRINTLN("Trying to start Arduino");

	// First init of static fields
	MainManager::get_manager();
	ConnectionManager::get_manager();

	//controller = new CommandsController();
	//connector = new ConnectionController();

	DEBUG_PRINTLN("Arduino was started");

	//connector->waitForConnection();
}

void loop()
{
	MainManager::get_manager()->run();
	//auto command = connector->getCommand();
	//if (command.length() >= 2)
	//{
	//	controller->handle(connector->getDevice(), command);
	//}
	//else
	//{
	//	DEBUG_PRINTLN("Command is short");
	//}
}
