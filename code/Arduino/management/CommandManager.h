#pragma once

#include <Arduino.h>
#include "../peripheral/SensorManager.h"
#include "../peripheral/EngineManager.h"
#include "../peripheral/ServoManager.h"
#include "../config/CommandsEnum.h"

/**
 * @brief Peripheral manager class (parse commands and execute it)
 * @attention First call of @getManager() method must be in setup() method
 */
class CommandManager
{
	static CommandManager* manager;

	CommandManager();
	CommandManager(CommandManager&);
	~CommandManager();

	SensorManager sensorsController;
	EngineManager moveController;
	ServoManager servoController;
	
	ApiVersion current_api = startBasicAPI;

	String parse_and_execute_command_connected(String command);
	String parse_and_execute_command_not_connected(String command);
	String run_movement_manager_connected(String command);
	String run_sensors_manager_connected(String command);
	String run_servo_manager_connected(String command);
	String run_commumication_manager_connected(String command);

public:
	static const ApiVersion min_api = APIWithCRC;
	static const ApiVersion max_api = APIWithCRC;

	static CommandManager* getManager();

	String parse_and_execute_command(String command);
};

