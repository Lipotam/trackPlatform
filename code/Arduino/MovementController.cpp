#include "MovementController.h"



MovementController::MovementController()
{
	pinMode(constants.left_engine_straight_pin, OUTPUT);
	pinMode(constants.left_engine_reverse_pin, OUTPUT);
	pinMode(constants.right_engine_straight_pin, OUTPUT);
	pinMode(constants.right_engine_reverse_pin, OUTPUT);

	digitalWrite(constants.left_engine_straight_pin, LOW);
	digitalWrite(constants.left_engine_reverse_pin, LOW);
	digitalWrite(constants.right_engine_straight_pin, LOW);
	digitalWrite(constants.right_engine_reverse_pin, LOW);
}

void MovementController::exec(ConnectingDevice *device, String command) {
	switch (command[0])
	{
	case forward:
		move_forward();
		break;
	case back:
		move_back();
		break;
	case left:
		turn_left();
		break;
	case right: 
		turn_right();
		break;
	case stop:
		stop_moving();
		break;
	default:
		break;
	}
}

void MovementController::move_forward() {
	digitalWrite(constants.left_engine_straight_pin, LOW);
	digitalWrite(constants.left_engine_reverse_pin, HIGH);
	digitalWrite(constants.right_engine_straight_pin, LOW);
	digitalWrite(constants.right_engine_reverse_pin, HIGH);
}

void MovementController::move_back() {
	digitalWrite(constants.left_engine_straight_pin, HIGH);
	digitalWrite(constants.left_engine_reverse_pin, LOW);
	digitalWrite(constants.right_engine_straight_pin, HIGH);
	digitalWrite(constants.right_engine_reverse_pin, LOW);

}

void MovementController::turn_left() {
	digitalWrite(constants.left_engine_straight_pin, LOW);
	digitalWrite(constants.left_engine_reverse_pin, HIGH);
	digitalWrite(constants.right_engine_straight_pin, HIGH);
	digitalWrite(constants.right_engine_reverse_pin, LOW);
}

void MovementController::turn_right() {
	digitalWrite(constants.left_engine_straight_pin, HIGH);
	digitalWrite(constants.left_engine_reverse_pin, LOW);
	digitalWrite(constants.right_engine_straight_pin, LOW);
	digitalWrite(constants.right_engine_reverse_pin, HIGH);
}

void MovementController::stop_moving() {
	digitalWrite(constants.left_engine_straight_pin, LOW);
	digitalWrite(constants.left_engine_reverse_pin, LOW);
	digitalWrite(constants.right_engine_straight_pin, LOW);
	digitalWrite(constants.right_engine_reverse_pin, LOW);
}

MovementController::~MovementController()
{
}
