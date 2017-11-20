#pragma once

#include <Arduino.h>
#include "../peripheral/SensorManager.h"
#include "../peripheral/EngineManager.h"
#include "../peripheral/ServoManager.h"

/**
 * @brief Peripheral manager class (parse commands and sends it)
 * @attention Create only one object of that class. And create it in setup() method only
 */
class CommandsController
{
	static CommandsController manager;

	CommandsController();
	CommandsController(CommandsController&);
	~CommandsController();

	SensorManager sensorsController;
	EngineManager moveController;
	ServoManager servoController;

public:
	static CommandsController& getManager();

	String parse_and_execute_command(String command);
};

