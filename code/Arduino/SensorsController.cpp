#include "SensorsController.h"



SensorsController::SensorsController()
{
}


void SensorsController::exec(ConnectingDevice *device, char command) {
	switch (command)
	{
	case trajectory_sensor: 
		device->send(getTrajectory());
		break;
	case distance_meter:
		device->send(getDistance());
		break;
	default:
		break;
	}
}

String SensorsController::getTrajectory() {
	return; //info
}

bool SensorsController::getLine() {
	return digitalRead(constants.line_1) ? true : false;
}

String SensorsController::getDistance() {
	uint16_t value = analogRead(constants.distance_ir_an);
	if (value < 10) { 
		value = 10;
	};
	return String(((67870.0 / (value - 3.0)) - 40.0));
}

SensorsController::~SensorsController()
{
}
