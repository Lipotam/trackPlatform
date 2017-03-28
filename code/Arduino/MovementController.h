#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "HardwareSerial.h" 
#include "Constants.h"


enum MoveEnum {
	forward = 0,
	left = 1,
	right = 2,
	back = 3,
	stop = 4
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

