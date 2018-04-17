#pragma once

#include "IBasicSensorManager.h"

// Line sensor board revision
// can be 1 or 2
#define LINE_SENSOR_REV 2

/**
 * @brief Get information from line sensors. Line values are returned as @AreaType values
 */
class LineSensorManager : public IBasicSensorManager
{
protected:
	void choose_sensor(int);

public:
	LineSensorManager();
	
	int get_sensor_value(int) override;
	int get_raw_sensor_value(int) override;
	int get_amount() override;
};

