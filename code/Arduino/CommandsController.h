#pragma once

#include "ConnectingDevice.h"
#include "MovementController.h"
#include "SensorsController.h"
#include "ServoController.h"

enum CommandsEnum {
	movementControllerID = '\001',
	sensorsControllerID = '\002',
	servoControllerID = '\003'
};

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

