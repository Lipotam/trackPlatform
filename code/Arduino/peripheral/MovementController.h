#pragma once

#include "../Constants.h"
#include "../CommandsEnum.h"

class MovementController
{	
	/**
	 * @brief All track control
	 * 
	 * @param speed Speed of control (must be in [-255, 255] ([-@MAX_SPEED, @MAX_SPEED]) range)
	 * @param enable_pin Pin to enable track
	 * @param straight_pin Pin to forward direction (LOW = enable forward direction)
	 * @param reverse_pin Pin to backward direction (LOW = enable backward direction)
	 */
	void track_control(int speed, const uint8_t enable_pin, const uint8_t straight_pin, const uint8_t reverse_pin);
	bool is_pin_num_good(const uint8_t pin);
	void left_track_control(const int speed);
	void right_track_control(const int speed);

public:
	MovementController();
	~MovementController();

	void move_forward(const int speed);
	void move_clockwose(const int speed);
	void set_track_speed(TrackIndex track_index, const int speed);
	void stop_moving();
};
