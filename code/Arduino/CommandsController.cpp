#include "CommandsController.h"



CommandsController::CommandsController()
{
}

void CommandsController::handle(ConnectingDevice *device, int command) 
{
	if (command > 0 && command < 10) {
		moveController.exec(command);
	}
	else if (command > 10 && command < 30) {
		sensorsController.exec(device, command);
	}
}


CommandsController::~CommandsController()
{
}
