#pragma once

#include "ConnectingDevice.h"
#include "MovementController.h"
#include "SensorsController.h"
#include "ServoController.h"
#include "CommandsEnum.h"

class CommandsController
{
private:
	MovementController moveController;
	SensorsController sensorsController;
	ServoController servoController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, String command);
	~CommandsController();
};

