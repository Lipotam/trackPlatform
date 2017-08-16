#pragma once

#include <Arduino.h>
#include "../connectors/ConnectingDevice.h"
#include "MainController.h"

/**
 * @brief Get information from sensors: line and distance. Distance values are returned in centimeters
 */
class SensorsController: public MainController
{
	int countDistanceSensors;
	int countLineSensors;
	int minimalLineBound;

public:
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

