#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "DistanceSensorManager.h"

DistanceSensorManager::DistanceSensorManager() : sensor_driver_(Constants::kDistanceSensorReadPin, 1080)
{
	pinMode(Constants::kDistanceSensorAPin, OUTPUT);
	pinMode(Constants::kDistanceSensorBPin, OUTPUT);
	pinMode(Constants::kDistanceSensorCPin, OUTPUT);
}

void DistanceSensorManager::choose_sensor(int number) {
	switch (number) {
	case 1:
		digitalWrite(Constants::kDistanceSensorAPin, HIGH);
		digitalWrite(Constants::kDistanceSensorBPin, LOW);
		digitalWrite(Constants::kDistanceSensorCPin, LOW);
		break;
	case 2:
		digitalWrite(Constants::kDistanceSensorAPin, LOW);
		digitalWrite(Constants::kDistanceSensorBPin, HIGH);
		digitalWrite(Constants::kDistanceSensorCPin, HIGH);
		break;
	case 3:
		digitalWrite(Constants::kDistanceSensorAPin, LOW);
		digitalWrite(Constants::kDistanceSensorBPin, LOW);
		digitalWrite(Constants::kDistanceSensorCPin, HIGH);
		break;
	case 4:
		digitalWrite(Constants::kDistanceSensorAPin, HIGH);
		digitalWrite(Constants::kDistanceSensorBPin, LOW);
		digitalWrite(Constants::kDistanceSensorCPin, HIGH);
		break;
	case 5:
		digitalWrite(Constants::kDistanceSensorAPin, HIGH);
		digitalWrite(Constants::kDistanceSensorBPin, HIGH);
		digitalWrite(Constants::kDistanceSensorCPin, HIGH);
		break;
	default:
		break;
	}
	delay(Constants::kSensorDelay);
}

int DistanceSensorManager::get_sensor_value(int number) {
	DEBUG_PRINTF("Get distance value from sensor %d\n", number);
	choose_sensor(number);
	return sensor_driver_.distance();
}

int DistanceSensorManager::get_raw_sensor_value(int number)
{
	DEBUG_PRINTF("Get distance raw value from sensor %d\n", number);
	choose_sensor(number);
	return analogRead(Constants::kDistanceSensorReadPin);
}

int DistanceSensorManager::get_amount()
{
	return Constants::kCountDistanceSensors;
}
