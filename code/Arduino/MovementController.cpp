#include "MovementController.h"



MovementController::MovementController()
{
	pinMode(constants.left_engine_1, OUTPUT);
	pinMode(constants.left_engine_2, OUTPUT);
	pinMode(constants.right_engine_1, OUTPUT);
	pinMode(constants.right_engine_2, OUTPUT);

	digitalWrite(constants.left_engine_1, LOW);
	digitalWrite(constants.left_engine_2, LOW);
	digitalWrite(constants.right_engine_1, LOW);
	digitalWrite(constants.right_engine_2, LOW);
}

void MovementController::exec(ConnectingDevice *device, int command) {
	switch (command)
	{
	case forward: 
		device->send("Move forward");
		move_forward();
		break;
	case back:
		device->send("Move back");
		move_back();
		break;
	case left:
		device->send("Turn left");
		turn_left();
		break;
	case right: 
		device->send("Turn right");
		turn_right();
		break;
	case stop:
		device->send("Stop");
		stop_moving();
		break;
	default:
		break;
	}
}

void MovementController::move_forward() {
	digitalWrite(constants.left_engine_1, HIGH);
	digitalWrite(constants.left_engine_2, LOW);
	digitalWrite(constants.right_engine_1, HIGH);
	digitalWrite(constants.right_engine_2, LOW);
}

void MovementController::move_back() {
	digitalWrite(constants.left_engine_1, LOW);
	digitalWrite(constants.left_engine_2, HIGH);
	digitalWrite(constants.right_engine_1, LOW);
	digitalWrite(constants.right_engine_2, HIGH);
}

void MovementController::turn_left() {
	digitalWrite(constants.left_engine_1, LOW);
	digitalWrite(constants.left_engine_2, HIGH);
	digitalWrite(constants.right_engine_1, HIGH);
	digitalWrite(constants.right_engine_2, LOW);
}

void MovementController::turn_right() {
	digitalWrite(constants.left_engine_1, HIGH);
	digitalWrite(constants.left_engine_2, LOW);
	digitalWrite(constants.right_engine_1, LOW);
	digitalWrite(constants.right_engine_2, HIGH);
}

void MovementController::stop_moving() {
	digitalWrite(constants.left_engine_1, LOW);
	digitalWrite(constants.left_engine_2, LOW);
	digitalWrite(constants.right_engine_1, LOW);
	digitalWrite(constants.right_engine_2, LOW);
}

MovementController::~MovementController()
{
}
