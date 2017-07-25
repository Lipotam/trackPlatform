#pragma once

#include <Arduino.h>
#include "peripheral/MovementController.h"
#include "peripheral/SensorsController.h"
#include "peripheral/ServoController.h"
#include "connectors/ConnectingDevice.h"

class CommandsController
{
	MovementController moveController;
	SensorsController sensorsController;
	ServoController servoController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, String command);
	~CommandsController();
};

