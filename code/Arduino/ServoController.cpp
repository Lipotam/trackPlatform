#include "ServoController.h"



ServoController::ServoController()
{
	
}

void ServoController::init() {
	servoHoriz.attach(constants.servo_horizontal_pin);
	servoVertical.attach(constants.servo_vertical_pin);
}

void ServoController::exec(ConnectingDevice* device, String command) {

}

void ServoController::setHorizontalAngle(int angle) {
	
	servoHoriz.write(angle);
}

void ServoController::setVerticalAngle(int angle) {
	servoVertical.write(angle);
}

void ServoController::setHorizontalAndVerticalAngle(int angleX, int angleY) {
	servoHoriz.write(angleX);
	servoVertical.write(angleY);
}

int ServoController::getHorizontalAngel() {
	return servoHoriz.read();
}

int ServoController::getVerticalAngel() {
	return servoVertical.read();
}


ServoController::~ServoController()
{
}
