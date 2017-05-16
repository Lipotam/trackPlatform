#pragma once

#include "MainController.h"



class MovementController : public MainController
{
private: 
	Constants constants;
	int MIN_SPEED;
	int MAX_SPEED;
	
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

