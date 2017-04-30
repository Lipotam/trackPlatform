#include "CommandsController.h"



CommandsController::CommandsController()
{
}

void CommandsController::handle(ConnectingDevice *device, String command) 
{
	switch (command[0]) {
	case movementControllerID:
		moveController.exec(device, command);
		break;
	case sensorsControllerID:
		sensorsController.exec(device, command);
		break;
	case test:
		Serial.println(command);
		break;
	default:
		break;
	}
}


CommandsController::~CommandsController()
{
}
