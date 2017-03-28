#include "SensorsController.h"



SensorsController::SensorsController()
{
}


void SensorsController::exec(ConnectingDevice *device, int command) {
	switch (command)
	{
	case trajectory_sensor: 
		device->send(getTrajectory());
		break;
	default:
		break;
	}
}

String SensorsController::getTrajectory() {
	return; //info
}


SensorsController::~SensorsController()
{
}
