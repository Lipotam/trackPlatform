#include "../config/CommandsEnum.h"
#include "../management/MainManager.h"
#include "../utils/ErrorManager.h"
#include "../config/Constants.h"
#include "../connection/DebugSerial.h"

#include "CommandManager.h"

CommandManager* CommandManager::manager_ = nullptr;

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
			current_api = static_cast<ApiVersion>(command[2]);
			if (current_api >= min_api && current_api <= max_api)
			{
				MainManager::get_manager()->set_current_connection();
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
	int* input_args = nullptr;
	DEBUG_PRINTLN("Movement command");

	switch (command[1]) {
	case track_set_speed:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 2);
		move_controller.set_track_speed(static_cast<TrackIndex>(input_args[0]), input_args[1]);
		break;
	case track_all_set_speed:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 2);
		move_controller.set_track_speed(left_track, input_args[0]);
		move_controller.set_track_speed(right_track, input_args[1]);
		break;
	case forward_speed:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 1);
		move_controller.move_forward(input_args[0]);
		break;
	case clockwise:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 1);
		move_controller.move_clockwose(input_args[0]);
		break;
	case stop:
		move_controller.stop_moving();
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

String CommandManager::run_sensors_manager_connected(String command)
{
	String res;
	DEBUG_PRINTLN("Sensors command");

	switch (command[1]) {
	case distance_sensor:
		res = get_sensor_value(command, distance_sensor_index, false);
		break;
	case distance_sensor_all:
		res = get_sensor_all_values(distance_sensor_index, false);
		break;
	case line_sensor:
		res = get_sensor_value(command, line_sensor_index, false);
		break;
	case line_sensor_all:
		res = get_sensor_all_values(line_sensor_index, false);
		break;
	case raw_distance_sensor:
		res = get_sensor_value(command, distance_sensor_index, true);
		break;
	case raw_distance_sensor_all:
		res = get_sensor_all_values(distance_sensor_index, true);
		break;
	case raw_line_sensor:
		res = get_sensor_value(command, line_sensor_index, true);
		break;
	case raw_line_sensor_all:
		res = get_sensor_all_values(line_sensor_index, true);
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
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 2);
		servo_controller.set_servo_degree(static_cast<ServoIndex>(input_args[0]), input_args[1]);
		break;
	case get_angle:
		input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 1);
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
		MainManager::get_manager()->reset_current_connection();
		break;
	case refreshConnectionCommunicationCommand:
		MainManager::get_manager()->reset_timer();
		break;
	default:
		ErrorManager::get_manager().set_error();
		DEBUG_PRINTLN("Cannot detect command");
		break;
	}

	return res;
}

String CommandManager::get_sensor_value(String command, SensorManagerIndex sensor_manager_index, bool is_raw)
{
	int* input_args = parametr_converter.parse_command(command, param_start_pos, Constants::kCommandsDelimetr, 1);
	const int res_num = sensors_controller.get_sensor_value(sensor_manager_index, input_args[0], is_raw);
	String res = String(res_num);

	if (input_args)
	{
		delete[] input_args;
	}
	return res;
}

String CommandManager::get_sensor_all_values(SensorManagerIndex sensor_manager_index, bool is_raw)
{
	int* res_nums = sensors_controller.get_all_sensors_value(sensor_manager_index, is_raw);
	const int amount = sensors_controller.get_amount(sensor_manager_index);
	String res = parametr_converter.int_array_to_string(res_nums, amount, Constants::kCommandsDelimetr);

	if (res_nums)
	{
		delete[] res_nums;
	}

	return res;
}

CommandManager* CommandManager::getManager()
{
	if (!manager_)
	{
		manager_ = new CommandManager();
	}
	return manager_;
}

String CommandManager::parse_and_execute_command(String command)
{
	String res;
	if (!MainManager::get_manager()->is_connected())
	{
		res = parse_and_execute_command_not_connected(command);
	}
	else
	{
		res = parse_and_execute_command_connected(command);
	}

	return res;
}

void CommandManager::stop_all()
{
	move_controller.stop_moving();
}

CommandManager::~CommandManager()
{
}
