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
	DEBUG_PRINTLN("Sensors command");

	switch (command[1]) {
	case distance_sensor:
		res = get_sensor_value(command, distance_sensor_index);
		break;
	case distance_sensor_all:
		res = get_sensor_all_values(distance_sensor_index);
		break;
	case line_sensor:
		res = get_sensor_value(command, line_sensor_index);
		break;
	case line_sensor_all:
		res = get_sensor_all_values(line_sensor_index);
		break;
	default:
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Cannot detect command");
		break;
	}

	return res;
}

String CommandManager::run_servo_manager_connected(String command)
{
	String res;
	int* input_args = nullptr;
	int res_num = 0;
	DEBUG_PRINTLN("Servo command");

	switch (command[1]) {
	case set_angle:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::commands_delimetr, 2);
		servo_controller.set_servo_degree(static_cast<ServoIndex>(input_args[0]), input_args[1]);
		break;
	case get_angle:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::commands_delimetr, 1);
		res_num = servo_controller.get_servo_degree(static_cast<ServoIndex>(input_args[0]));
		res = String(res_num);
		break;
	default:
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Cannot detect command");
		break;
	}

	if (input_args)
	{
		delete[] input_args;
	}

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

String CommandManager::get_sensor_value(String command, SensorManagerIndex sensor_manager_index)
{
	int* input_args = parametr_converter.parse_command(command, param_start_pos, Constants::commands_delimetr, 1);
	const int res_num = sensors_controller.get_sensor_value(sensor_manager_index, input_args[0]);
	String res = String(res_num);

	if (input_args)
	{
		delete[] input_args;
	}
	return res;
}

String CommandManager::get_sensor_all_values(SensorManagerIndex sensor_manager_index)
{
	int* res_nums = sensors_controller.get_all_sensors_value(sensor_manager_index);
	const int amount = sensors_controller.get_amount(sensor_manager_index);
	String res = parametr_converter.int_array_to_string(res_nums, amount, Constants::commands_delimetr);

	if (res_nums)
	{
		delete[] res_nums;
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
