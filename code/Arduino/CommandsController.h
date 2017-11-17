#pragma once

#include <Arduino.h>
#include "peripheral/SensorsController.h"
#include "peripheral/EngineManager.h"
#include "peripheral/ServoController.h"
#include "connectors/ConnectingDevice.h"

/**
 * @brief Peripheral manager class (parse commands and sends it)
 * @attention Create only one object of that class. And create it in setup() method only
 */
class CommandsController
{
	SensorsController sensorsController;
	EngineManager moveController;
	ServoController servoController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, String command);
	~CommandsController();
};

