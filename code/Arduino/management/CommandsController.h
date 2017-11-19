#pragma once

#include <Arduino.h>
#include "../peripheral/SensorManager.h"
#include "../peripheral/EngineManager.h"
#include "../peripheral/ServoManager.h"
#include "../connection/ConnectingDevice.h"

/**
 * @brief Peripheral manager class (parse commands and sends it)
 * @attention Create only one object of that class. And create it in setup() method only
 */
class CommandsController
{
	SensorManager sensorsController;
	EngineManager moveController;
	ServoManager servoController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, String command);
	~CommandsController();
};

