#include "../config/CommandsEnum.h"
#include "SensorManager.h"
#include "DistanceSensorManager.h"
#include "LineSensorManager.h"

IBasicSensorManager*& SensorManager::get_manager(SensorManagerIndex sensor_manager_index)
{
	return sensor_managers[sensor_manager_index];
}

SensorManager::SensorManager() : managers_num(2)
{
	sensor_managers = new IBasicSensorManager*[managers_num];
	get_manager(line_sensor_index) = new LineSensorManager();
	get_manager(distance_sensor_index) = new DistanceSensorManager();
}

SensorManager::~SensorManager()
{
	if (sensor_managers) {
		for (int i = 0; i < managers_num; ++i) {
			if (sensor_managers[i]) {
				delete sensor_managers[i];
			}
		}

		delete[] sensor_managers;
	}
}

int SensorManager::get_sensor_value(SensorManagerIndex sensor_manager_index, int sensor_number, bool is_raw)
{
	return (is_raw
		? get_manager(sensor_manager_index)->get_raw_sensor_value(sensor_number)
		: get_manager(sensor_manager_index)->get_sensor_value(sensor_number)
		);
}

int* SensorManager::get_all_sensors_value(SensorManagerIndex sensor_manager_index, bool is_raw)
{
	const int sensor_amount = get_amount(sensor_manager_index);
	int* arr = new int[sensor_amount];
	for (int i = 0; i < sensor_amount; i++) {
		arr[i] = get_sensor_value(sensor_manager_index, i + 1, is_raw);
	}
	return arr;
}

int SensorManager::get_amount(SensorManagerIndex sensor_manager_index)
{
	return get_manager(sensor_manager_index)->get_amount();
}
