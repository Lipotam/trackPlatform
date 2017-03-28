#pragma once

#include "ConnectingDevice.h"

enum SensorsEnum {
	distance_meter = 10,
	distance_meter_2,
	distance_meter_3,
	distance_meter_4,
	distance_meter_5,

	trajectory_sensor
};

class SensorsController
{
public:
	SensorsController();
	void exec(ConnectingDevice*, int);
	String getTrajectory();
	~SensorsController();
};

