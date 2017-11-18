#include "../config/CommandsEnum.h"
#include "CommandsController.h"

CommandsController::CommandsController()
{
}

void CommandsController::handle(ConnectingDevice *device, String command) 
{
	switch (command[0]) {
	case movementControllerID:
		//moveController.exec(device, command);			//TODO: fix
		break;
	case sensorsControllerID:
		//sensorsController.exec(device, command);		//TODO: fix
		break;
	case servoControllerID:
		//servoController.exec(device, command);		//TODO: fix
		break;
	default:
		break;
	}
}

CommandsController::~CommandsController()
{
}
