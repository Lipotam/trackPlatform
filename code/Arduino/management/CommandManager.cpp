#include "../config/CommandsEnum.h"
#include "CommandManager.h"

CommandManager* CommandManager::manager = nullptr;

CommandManager::CommandManager()
{
}

CommandManager::CommandManager(CommandManager&)
{
}

CommandManager* CommandManager::getManager()
{
	if (!manager)
	{
		manager = new CommandManager();
	}
	return manager;
}

String CommandManager::parse_and_execute_command(String command) 
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

CommandManager::~CommandManager()
{
}
