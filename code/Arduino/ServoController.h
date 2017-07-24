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

	void init();
public:
	Constants constants;
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

