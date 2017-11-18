#pragma once

#include "IBasicSensorManager.h"

/**
 * @brief Get information from line sensors. Line values are returned as @AreaType values
 */
class LineSensorManager : IBasicSensorManager
{
	int sensor_amount;

protected:
	void choose_sensor(int);

public:
	LineSensorManager();
	
	int get_sensor_value(int) override;
};

