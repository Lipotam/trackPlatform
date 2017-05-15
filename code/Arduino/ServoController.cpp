#include "ServoController.h"



ServoController::ServoController()
{
	
}

void ServoController::init() {
	horizontalServo.attach(constants.servo_horizontal_pin);
	verticalServo.attach(constants.servo_vertical_pin);
}

void ServoController::exec(ConnectingDevice* device, String command) {

}

void ServoController::setHorizontalAngle(int angle) {
	
	horizontalServo.write(angle);
}

void ServoController::setVerticalAngle(int angle) {
	verticalServo.write(angle);
}

void ServoController::setHorizontalAndVerticalAngle(int angleX, int angleY) {
	horizontalServo.write(angleX);
	verticalServo.write(angleY);
}

int ServoController::getHorizontalAngel() {
	return horizontalServo.read();
}

int ServoController::getVerticalAngel() {
	return verticalServo.read();
}


ServoController::~ServoController()
{
}
