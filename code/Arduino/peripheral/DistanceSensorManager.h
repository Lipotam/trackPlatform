#pragma once

#include "IBasicSensorManager.h"
#include "SharpIR.h"

/**
 * @brief Get information from distance sensors. Values are returned in centimeters
 */
class DistanceSensorManager : public IBasicSensorManager
{
protected:
	SharpIR sensor_driver_;
	void choose_sensor(int number);

public:
	DistanceSensorManager();

	/**
	 * @brief Get sensor value in sentimeters.
	 *			Calculate value by formula:
	 *				res = a / volts + b,
	 *			where
	 *				a, b - constants
	 *				volts - current voltage from sensor pin (mapped to 1023 as max value)
	 */
	int get_sensor_value(int) override;
	int get_raw_sensor_value(int) override;
	int get_amount() override;
};

