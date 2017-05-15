#pragma once
#include <Servo.h>
#include "Constants.h"
#include "ConnectingDevice.h"

class ServoController
{
private:
	Servo horizontalServo;
	Servo verticalServo;

public:
	Constants constants;
	ServoController();
	void init();
	void exec(ConnectingDevice*, String);
	void setHorizontalAngle(int angle);
	void setVerticalAngle(int angle);
	void setHorizontalAndVerticalAngle(int angleX, int angleY);
	int getHorizontalAngel();
	int getVerticalAngel();
	~ServoController();
};

