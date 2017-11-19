#include "../config/CommandsEnum.h"
#include "../connection/DebugSerial.h"
#include "EngineManager.h"

void EngineManager::track_control(int speed, const uint8_t enable_pin, const uint8_t straight_pin, const uint8_t reverse_pin)
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

bool EngineManager::is_pin_num_good(const uint8_t pin)
{
	return (pin <= A15);
}

EngineManager::EngineManager()
{
	pinMode(Constants::left_engine_enable, OUTPUT);
	pinMode(Constants::left_engine_straight_pin, OUTPUT);
	pinMode(Constants::left_engine_reverse_pin, OUTPUT);
	pinMode(Constants::right_engine_straight_pin, OUTPUT);
	pinMode(Constants::right_engine_reverse_pin, OUTPUT);
	pinMode(Constants::right_engine_enable, OUTPUT);

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
	right_track_control(speed);
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
	set_track_speed(left_track, Constants::min_speed);
	set_track_speed(right_track, Constants::min_speed);
}

void EngineManager::left_track_control(const int speed) {
	track_control(speed, Constants::left_engine_enable, Constants::left_engine_straight_pin, Constants::left_engine_reverse_pin);
}

void EngineManager::right_track_control(const int speed) {
	track_control(speed, Constants::right_engine_enable, Constants::right_engine_straight_pin, Constants::right_engine_reverse_pin);
}

EngineManager::~EngineManager()
{
}
