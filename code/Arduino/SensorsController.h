#pragma once

#include "ConnectingDevice.h"
#include "Constants.h"
#include "Arduino.h"
#include "MainController.h"
#include "CommandsEnum.h"



class SensorsController: public MainController
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

	~SensorsController();
};

