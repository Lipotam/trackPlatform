#pragma once

#include "ConnectingDevice.h"
#include "MovementController.h"
#include "SensorsController.h"

class CommandsController
{
private:
	MovementController moveController;
	SensorsController sensorsController;

public:
	CommandsController();
	void handle(ConnectingDevice *device, int command);
	~CommandsController();
};

