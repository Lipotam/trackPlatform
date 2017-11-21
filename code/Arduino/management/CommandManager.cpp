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
		res = run_movement_manager_connected(command);
		break;
	case sensorsControllerID:
		res = run_sensors_manager_connected(command);
		break;
	case servoControllerID:
		res = run_servo_manager_connected(command);
		break;
	case communicationControllerID:
		res = run_commumication_manager_connected(command);
		break;
	default:
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Cannot detect manager");
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

String CommandManager::run_movement_manager_connected(String command)
{
	String res;
	//TODO
	DEBUG_PRINTLN("Movement command");
	return res;
}

String CommandManager::run_sensors_manager_connected(String command)
{
	String res;
	//TODO
	DEBUG_PRINTLN("Sensors command");
	return res;
}

String CommandManager::run_servo_manager_connected(String command)
{
	String res;
	//TODO
	DEBUG_PRINTLN("Servo command");
	return res;
}

String CommandManager::run_commumication_manager_connected(String command)
{
	String res;
	DEBUG_PRINTLN("Communication command");

	switch (command[1]) {
	case stopCommunicationCommand:
		ConnectionManager::get_manager()->reset_current_connection();
		break;
	case refreshConnectionCommunicationCommand:
		ConnectionManager::get_manager()->reset_timer();
		break;
	default:
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Cannot detect command");
		break;
	}

	return res;
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
