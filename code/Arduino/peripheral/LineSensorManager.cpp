#include "../connectors/DebugSerial.h"
#include "LineSensorManager.h"

LineSensorManager::LineSensorManager()
{
	pinMode(Constants::line_sensor_a_pin, OUTPUT);
	pinMode(Constants::line_sensor_b_pin, OUTPUT);
	pinMode(Constants::line_sensor_c_pin, OUTPUT);
}

void LineSensorManager::choose_sensor(int number) {
	switch (number) {
		case 1:
			digitalWrite(Constants::line_sensor_a_pin, LOW);
			digitalWrite(Constants::line_sensor_b_pin, LOW);
			digitalWrite(Constants::line_sensor_c_pin, HIGH);
			break;
		case 2:
			digitalWrite(Constants::line_sensor_a_pin, HIGH);
			digitalWrite(Constants::line_sensor_b_pin, HIGH);
			digitalWrite(Constants::line_sensor_c_pin, HIGH);
			break;
		case 3:
			digitalWrite(Constants::line_sensor_a_pin, HIGH);
			digitalWrite(Constants::line_sensor_b_pin, LOW);
			digitalWrite(Constants::line_sensor_c_pin, HIGH);
			break;
		case 4:
			digitalWrite(Constants::line_sensor_a_pin, LOW);
			digitalWrite(Constants::line_sensor_b_pin, HIGH);
			digitalWrite(Constants::line_sensor_c_pin, HIGH);
			break;
		case 5:
			digitalWrite(Constants::line_sensor_a_pin, HIGH);
			digitalWrite(Constants::line_sensor_b_pin, LOW);
			digitalWrite(Constants::line_sensor_c_pin, LOW);
			break;
		default:
			break;
	}
}

int LineSensorManager::get_sensor_value(int number) {
	DEBUG_PRINTF("Get line value from sensor %d\n", number);
	choose_sensor(number);
	return (analogRead(Constants::line_sensor_read_pin) > Constants::minimal_line_bound) ? 1 : 0;
}

int LineSensorManager::get_amount()
{
	return Constants::count_line_sensors;
}
