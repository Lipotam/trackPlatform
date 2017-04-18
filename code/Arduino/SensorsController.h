#pragma once

#include "ConnectingDevice.h"
#include "Constants.h"
#include "MainController.h"
#include "SharpIR.h"

enum SensorsEnum {
	distance_sensor = '\001',
	distance_sensor_2 = '\002',
	distance_sensor_3 = '\003',
	distance_sensor_4 = '\004',
	distance_sensor_5 = '\005',

	trajectory_sensor = '\006'
};

class SensorsController : public MainController
{
private:
	SharpIR *sharp;
public:
	Constants constants;
	SensorsController();
	void exec(ConnectingDevice*, String);
	String getTrajectory();
	String getDistance();
	bool getLine();
	~SensorsController();
};

