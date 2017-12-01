#include "../config/Constants.h"
#include "../connection/DebugSerial.h"
#include "EngineManager.h"

void EngineManager::manage_track(int speed, const uint8_t enable_pin, const uint8_t straight_pin, const uint8_t reverse_pin)
{
	if (!is_pin_num_good(enable_pin) || !is_pin_num_good(straight_pin) || !is_pin_num_good(reverse_pin)) {
		return;
	}

	const bool is_forward = (speed >= 0);
	speed *= is_forward ? 1 : -1;
	speed = (speed > Constants::kMaxSpeed) ? Constants::kMaxSpeed : speed;

	analogWrite(enable_pin, speed);
	digitalWrite(straight_pin, is_forward ? HIGH : LOW);
	digitalWrite(reverse_pin, is_forward ? LOW : HIGH);
}

bool EngineManager::is_pin_num_good(const uint8_t pin)
{
	return (pin <= max_pin_num);
}

EngineManager::EngineManager()
{
	pinMode(Constants::kLeftEngineEnable, OUTPUT);
	pinMode(Constants::kLeftEngineStraightPin, OUTPUT);
	pinMode(Constants::kLeftEngineReversePin, OUTPUT);
	pinMode(Constants::kRightEngineStraightPin, OUTPUT);
	pinMode(Constants::kRightEngineReversePin, OUTPUT);
	pinMode(Constants::kRightEngineEnable, OUTPUT);

	stop_moving();
}

void EngineManager::move_forward(const int speed) {
	DEBUG_PRINTF("Move forward with speed %d\n", speed);
	left_track_control(speed);
	right_track_control(speed);
}

void EngineManager::move_clockwose(const int speed) {
	DEBUG_PRINTF("Turn right with speed %d\n", speed);
	left_track_control(speed);
	right_track_control(-speed);
}

void EngineManager::set_track_speed(TrackIndex track_index, const int speed)
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

void EngineManager::stop_moving() {
	DEBUG_PRINTF("Stop moving\n");
	set_track_speed(left_track, Constants::kMinSpeed);
	set_track_speed(right_track, Constants::kMinSpeed);
}

void EngineManager::left_track_control(const int speed) {
	manage_track(speed, Constants::kLeftEngineEnable, Constants::kLeftEngineStraightPin, Constants::kLeftEngineReversePin);
}

void EngineManager::right_track_control(const int speed) {
	manage_track(speed, Constants::kRightEngineEnable, Constants::kRightEngineStraightPin, Constants::kRightEngineReversePin);
}

EngineManager::~EngineManager()
{
}
