#pragma once

#include "ConnectingDevice.h"
#include "Constants.h"

enum SensorsEnum {
	distance_meter = '\001',
	distance_meter_2 = '\002',
	distance_meter_3 = '\003',
	distance_meter_4 = '\004',
	distance_meter_5 = '\006',

	trajectory_sensor = '\007'
};

class SensorsController
{

public:
	Constants constants;
	SensorsController();
	void exec(ConnectingDevice*, char);
	String getTrajectory();
	String getDistance();
	bool getLine();
	~SensorsController();
};

