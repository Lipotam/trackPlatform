#pragma once

#include "../connectors/ConnectingDevice.h"
#include "MainController.h"

class MovementController : public MainController
{
	Constants constants;
	int MIN_SPEED;
	int MAX_SPEED;
	
	/**
	 * @brief All track control
	 * 
	 * @param direction Main direction (what direction will be positive in @speed param)
	 * @param speed Speed of control (must be in [-255, 255] ([-@MAX_SPEED, @MAX_SPEED]) range)
	 * @param enablePin Pin to enable track
	 * @param straightPin Pin to forward direction (LOW = enable forward direction)
	 * @param reversePin Pin to backward direction (LOW = enable backward direction)
	 */
	void track_control(bool direction, int speed, uint8_t enablePin, uint8_t straightPin, uint8_t reversePin);

	static bool isPinNumGood(uint8_t pin);
public:
	MovementController();
	void exec(ConnectingDevice *device, String);
	void move_forward();
	void move_forward(int speed);
	void move_forward(int speed, int time_ms);
	void move_back();
	void move_back(int speed);
	void turn_left();
	void turn_right();
	void left_track_control(bool direction, int speed);
	void right_track_control(bool direction, int speed);
	void choose_track_set_speed(int trackID, int speed);
	void choose_track_set_speed(int* arr);
	void stop_moving();
	~MovementController();
};
