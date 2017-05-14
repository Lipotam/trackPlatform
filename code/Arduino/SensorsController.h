#pragma once

#include "ConnectingDevice.h"
#include "Constants.h"
#include "Arduino.h"
#include "MainController.h"
#include "SharpIR.h"

enum SensorsEnum {
	distance_sensor_1 = '\001',
	distance_sensor_2 = '\002',
	distance_sensor_3 = '\003',
	distance_sensor_4 = '\004',
	distance_sensor_5 = '\005',
	distance_sensor_all = '\006',

	line_sensor_1 = '\007',
	line_sensor_2 = '\008',
	line_sensor_3 = '\009',
	line_sensor_4 = '\010',
	line_sensor_5 = '\011',
	line_sensor_all = '\012'
};


class SensorsController
{
private:
	int countDistanceSensors;
	int countLineSensors;
	SharpIR *sharp;
public:
	Constants constants;
	SensorsController();
	void exec(ConnectingDevice*, String);
	
	int getDistance(int);
	int* getDistanceAll();
	void chooseDistanceSensor(int);

	void chooseLineSensor(int);
	int getLine(int);
	int* getLineAll();

	String intArrayToString(int*, int);
	~SensorsController();
};

