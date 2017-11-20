#include "../config/CommandsEnum.h"
#include "../connection/ConnectionManager.h"
#include "../utils/ErrorManager.h"
#include "../connection/DebugSerial.h"

#include "CommandManager.h"

CommandManager* CommandManager::manager = nullptr;

CommandManager::CommandManager()
{
}

CommandManager::CommandManager(CommandManager&)
{
}

String CommandManager::parse_and_execute_command_connected(String command)
{
	String res;
	if (command.length() < 2)
	{
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Command is too short");
		return res;
	}

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
	return res;
}

String CommandManager::parse_and_execute_command_not_connected(String command)
{
	ErrorManager::get_manager().set_error();
	if (command.length() > 2)
	{
		if (command[0] == communicationControllerID && 
			command[1] == startCommunicationCommand)
		{
			if (command[2] >= min_api && command[2] <= max_api)
			{
				current_api = static_cast<ApiVersion>(command[2]);
				ConnectionManager::get_manager()->set_current_connection();
				ErrorManager::get_manager().reset_error();
				DEBUG_PRINTF("Connected with API %d\n", current_api);
			}
			else
			{
				DEBUG_PRINTF("Cannot connect with API %d. Minimum required %d, maximum %d\n", current_api, min_api, max_api);
			}
		}
		else
		{
			DEBUG_PRINT("Bad command ");
			DEBUG_PRINTLNHEX(command.substring(2));
		}
	}
	return "";
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
	String res;
	if (!ConnectionManager::get_manager()->is_connected())
	{
		res = parse_and_execute_command_not_connected(command);
	}
	else
	{
		res = parse_and_execute_command_connected(command);
	}

	return res;
}

CommandManager::~CommandManager()
{
}
