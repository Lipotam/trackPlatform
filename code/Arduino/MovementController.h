#pragma once

#include "Arduino.h"

#include "HardwareSerial.h" 
#include "Constants.h"
#include "ConnectingDevice.h"
#include "MainController.h"



enum MoveEnum {
	forward = '\001',
	left = '\002',
	right = '\003',
	back = '\004',
	stop = '\005'
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
	void exec(ConnectingDevice *device, String);
	~MovementController();
};

