#pragma once

/**
 * @brief Basic sensor manager interface (abstract class)
 */
class IBasicSensorManager
{
public:
	virtual ~IBasicSensorManager() = default;
	
	virtual int get_sensor_value(int) = 0;
	virtual int get_raw_sensor_value(int) = 0;
	virtual int get_amount() = 0;
};

