#pragma once
#include <Servo.h>
#include "Constants.h"
#include "ConnectingDevice.h"
#include "MainController.h"

class ServoController : public MainController
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
	void setHorizontalAndVerticalAngle(int* arr);
	int getHorizontalAngel();
	int getVerticalAngel();
	int* getCoordinates();
	~ServoController();
};

