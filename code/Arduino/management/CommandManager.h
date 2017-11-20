#pragma once

#include <Arduino.h>
#include "../peripheral/SensorManager.h"
#include "../peripheral/EngineManager.h"
#include "../peripheral/ServoManager.h"

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

public:
	static CommandManager* getManager();

	String parse_and_execute_command(String command);
};

