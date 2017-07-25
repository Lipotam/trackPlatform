#include "CommandsEnum.h"
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
	case servoControllerID:
		servoController.exec(device, command);
		break;
	default:
		break;
	}
}

CommandsController::~CommandsController()
{
}
