#pragma once

#include <Arduino.h>
#include "../peripheral/SensorManager.h"
#include "../peripheral/EngineManager.h"
#include "../peripheral/ServoManager.h"
#include "../config/CommandsEnum.h"
#include "../utils/Converter.h"

/**
 * @brief Peripheral manager class (parse commands and execute it)
 * @attention First call of @getManager() method must be in setup() method
 */
class CommandManager
{
	static CommandManager* manager_;

	CommandManager();
	CommandManager(CommandManager&);
	~CommandManager();

	SensorManager sensors_controller;
	EngineManager move_controller;
	ServoManager servo_controller;
	Converter parametr_converter;
	
	ApiVersion current_api = startBasicAPI;
	const int param_start_pos = 2;

	String parse_and_execute_command_connected(String command);
	String parse_and_execute_command_not_connected(String command);
	String run_movement_manager_connected(String command);
	String run_sensors_manager_connected(String command);
	String run_servo_manager_connected(String command);
	String run_commumication_manager_connected(String command);

	String get_sensor_value(String command, SensorManagerIndex sensor_manager_index, bool is_raw);
	String get_sensor_all_values(SensorManagerIndex sensor_manager_index, bool is_raw);

public:
	static const ApiVersion min_api = APIWithCRC;
	static const ApiVersion max_api = APIWithCRC;

	static CommandManager* getManager();

	String parse_and_execute_command(String command);

	void stop_all();
};

