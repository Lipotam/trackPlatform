#pragma once
#include <Servo.h>
#include "Constants.h"
#include "ConnectingDevice.h"


enum ServoEnum {
	
};

class ServoController
{
private:
	Servo servoHoriz;
	Servo servoVertical;

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

