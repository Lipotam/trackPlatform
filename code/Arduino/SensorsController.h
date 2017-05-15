#pragma once

#include "ConnectingDevice.h"
#include "Constants.h"
#include "Arduino.h"
#include "MainController.h"
#include "CommandsEnum.h"



class SensorsController
{
private:
	int countDistanceSensors;
	int countLineSensors;
	int minimalLineBound;

public:
	Constants constants;
	SensorsController();
	void exec(ConnectingDevice*, String);
	
	int getDistance(int);
	int* getDistanceAll();
	void chooseDistanceSensor(int);
	int* getDistanceNTime(int number, int n);
	int getAverageDistance(int number, int n);


	void chooseLineSensor(int);
	int getLine(int);
	int* getLineAll();

	String intArrayToString(int*, int);
	~SensorsController();
};

