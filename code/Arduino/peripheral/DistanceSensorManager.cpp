#include "../connectors/DebugSerial.h"
#include "../Constants.h"
#include "DistanceSensorManager.h"

DistanceSensorManager::DistanceSensorManager()
{
	pinMode(Constants::distance_sensor_a_pin, OUTPUT);
	pinMode(Constants::distance_sensor_b_pin, OUTPUT);
	pinMode(Constants::distance_sensor_c_pin, OUTPUT);
}

void DistanceSensorManager::choose_sensor(int number) {
	switch (number) {
	case 1:
		digitalWrite(Constants::distance_sensor_a_pin, HIGH);
		digitalWrite(Constants::distance_sensor_b_pin, LOW);
		digitalWrite(Constants::distance_sensor_c_pin, LOW);
		break;
	case 2:
		digitalWrite(Constants::distance_sensor_a_pin, LOW);
		digitalWrite(Constants::distance_sensor_b_pin, HIGH);
		digitalWrite(Constants::distance_sensor_c_pin, HIGH);
		break;
	case 3:
		digitalWrite(Constants::distance_sensor_a_pin, LOW);
		digitalWrite(Constants::distance_sensor_b_pin, LOW);
		digitalWrite(Constants::distance_sensor_c_pin, HIGH);
		break;
	case 4:
		digitalWrite(Constants::distance_sensor_a_pin, HIGH);
		digitalWrite(Constants::distance_sensor_b_pin, LOW);
		digitalWrite(Constants::distance_sensor_c_pin, HIGH);
		break;
	case 5:
		digitalWrite(Constants::distance_sensor_a_pin, HIGH);
		digitalWrite(Constants::distance_sensor_b_pin, HIGH);
		digitalWrite(Constants::distance_sensor_c_pin, HIGH);
		break;
	default:
		break;
	}
}

int DistanceSensorManager::get_sensor_value(int number) {
	DEBUG_PRINTF("Get distance value from sensor %d\n", number);
	choose_sensor(number);
	float volts = static_cast<float>(analogRead(Constants::distance_sensor_read_pin));
	if (volts == 0)
	{
		DEBUG_PRINTLN("Distance volts were 0");
		return -1;
	}
	float distance = (Constants::distance_calculation_a / (volts)) + Constants::distance_calculation_b;
	DEBUG_PRINTF("Distance volts = %d, dist * 10000 = %06ld\n", static_cast<int>(volts), static_cast<long>(distance * 10000));
	return distance;
}

int DistanceSensorManager::get_amount()
{
	return Constants::count_distance_sensors;
}
