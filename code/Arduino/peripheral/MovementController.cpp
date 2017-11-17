#include "../CommandsEnum.h"
#include "../connectors/DebugSerial.h"
#include "MovementController.h"

void MovementController::track_control(int speed, const uint8_t enable_pin, const uint8_t straight_pin, const uint8_t reverse_pin)
{
	if (!is_pin_num_good(enable_pin) || !is_pin_num_good(straight_pin) || !is_pin_num_good(reverse_pin)) {
		return;
	}

	const bool is_forward = (speed >= 0);
	speed *= is_forward ? 1 : -1;
	speed = (speed > Constants::max_speed) ? Constants::max_speed : speed;

	analogWrite(enable_pin, speed);
	digitalWrite(straight_pin, is_forward ? HIGH : LOW);
	digitalWrite(reverse_pin, is_forward ? LOW : HIGH);
}

bool MovementController::is_pin_num_good(const uint8_t pin)
{
	return (pin <= A15);
}

MovementController::MovementController()
{
	pinMode(constants.left_engine_enable, OUTPUT);
	pinMode(constants.left_engine_straight_pin, OUTPUT);
	pinMode(constants.left_engine_reverse_pin, OUTPUT);
	pinMode(constants.right_engine_straight_pin, OUTPUT);
	pinMode(constants.right_engine_reverse_pin, OUTPUT);
	pinMode(constants.right_engine_enable, OUTPUT);

	stop_moving();
}

void MovementController::move_forward(const int speed) {
	DEBUG_PRINTF("Move forward with speed %d\n", speed);
	left_track_control(speed);
	right_track_control(speed);
}

void MovementController::move_clockwose(const int speed) {
	DEBUG_PRINTF("Turn right with speed %d\n", speed);
	left_track_control(speed);
	right_track_control(speed);
}

void MovementController::set_track_speed(TrackIndex track_index, const int speed)
{
	DEBUG_PRINTF("Set track %d speed %d\n", track_index, speed);
	if (track_index == left_track)
	{
		left_track_control(speed);
	}
	else
	{
		right_track_control(speed);
	}
}

void MovementController::stop_moving() {
	DEBUG_PRINTF("Stop moving\n");
	set_track_speed(left_track, Constants::min_speed);
	set_track_speed(right_track, Constants::min_speed);
}

void MovementController::left_track_control(const int speed) {
	track_control(speed, constants.left_engine_enable, constants.left_engine_straight_pin, constants.left_engine_reverse_pin);
}

void MovementController::right_track_control(const int speed) {
	track_control(speed, constants.right_engine_enable, constants.right_engine_straight_pin, constants.right_engine_reverse_pin);
}

MovementController::~MovementController()
{
}
