#include "SensorsController.h"



SensorsController::SensorsController()
{
	//¸sharp = new SharpIR(GP2Y0A21YK0F, A0);
}


void SensorsController::exec(ConnectingDevice *device, String command) {
	switch (command[1])
	{
	case trajectory_sensor: 
		device->send(getTrajectory());
		break;
	case distance_sensor:
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
	return digitalRead(constants.line_sensor_pin) ? true : false;
}

String SensorsController::getDistance() {
	//return String(sharp->getDistance());
}

SensorsController::~SensorsController()
{
}
