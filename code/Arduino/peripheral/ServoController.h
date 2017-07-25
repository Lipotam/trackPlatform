#pragma once
#include <Servo.h>
#include "MainController.h"

class ServoController : public MainController
{
	Servo horizontalServo;
	Servo verticalServo;

	void init();

public:
	ServoController();
	void exec(ConnectingDevice*, String);
	void setHorizontalAngle(int angle);
	void setVerticalAngle(int angle);
	void setHorizontalAndVerticalAngle(int angleX, int angleY);
	void setHorizontalAndVerticalAngle(int* arr);
	int getHorizontalAngel();
	int getVerticalAngel();
	int* getCoordinates();
	~ServoController();
};

