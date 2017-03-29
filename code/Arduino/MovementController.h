#pragma once

#include "Arduino.h"

#include "HardwareSerial.h" 
#include "Constants.h"


enum MoveEnum {
	forward = 1,
	left ,
	right,
	back,
	stop
};


class MovementController
{
private: 
	Constants constants;
	void move_forward();
	void move_back();
	void turn_left();
	void turn_right();
	void stop_moving();

public:
	MovementController();
	void exec(int);
	~MovementController();
};

