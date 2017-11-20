#include "../config/CommandsEnum.h"
#include "CommandsController.h"

CommandsController CommandsController::manager;

CommandsController::CommandsController()
{
}

CommandsController::CommandsController(CommandsController&)
{
}

CommandsController& CommandsController::getManager()
{
	return manager;
}

String CommandsController::parse_and_execute_command(String command) 
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
