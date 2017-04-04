#include "CommandsController.h"



CommandsController::CommandsController()
{
}

void CommandsController::handle(ConnectingDevice *device, String command) 
{
	switch (command[0]) {
	case movementControllerID:
		moveController.exec(device, command[1]);
		break;
	case sensorsControllerID:
		sensorsController.exec(device, command[1]);
		break;
	default:
		break;
	}
}


CommandsController::~CommandsController()
{
}
