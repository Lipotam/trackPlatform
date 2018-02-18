#pragma once

#include "../config/CommandsEnum.h"
#include "IBasicSensorManager.h"

/**
 * @brief Get information from sensors: line and distance. Distance values are returned in centimeters
 */
class SensorManager
{
	const int managers_num;
	IBasicSensorManager** sensor_managers;

	IBasicSensorManager*& get_manager(SensorManagerIndex sensor_manager_index);

public:
	SensorManager();
	~SensorManager();
	
	int get_sensor_value(SensorManagerIndex sensor_manager_index, int sensor_number, bool is_raw);
	int* get_all_sensors_value(SensorManagerIndex sensor_manager_index, bool is_raw);

	int get_amount(SensorManagerIndex sensor_manager_index);
};

