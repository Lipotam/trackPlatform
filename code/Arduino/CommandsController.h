#pragma once

#include "ConnectingDevice.h"
#include "MovementController.h"
#include "SensorsController.h"

enum CommandsEnum {
	movementControllerID = '\001',
	sensorsControllerID = '\002'
};

class CommandsController
{
private:
	MovementController moveController;
	SensorsController sensorsController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, String command);
	~CommandsController();
};

