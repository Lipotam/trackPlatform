#pragma once
#include <Servo.h>
#include "MainController.h"

/**
 * @brief Servo controller for 2 axes: X & Y
 * @attention Create only one object of that class. And create it in setup() method only
 */
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

