#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "DistanceSensorManager.h"

DistanceSensorManager::DistanceSensorManager()
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
}

int DistanceSensorManager::get_sensor_value(int number) {
	DEBUG_PRINTF("Get distance value from sensor %d\n", number);
	choose_sensor(number);
	float volts = static_cast<float>(analogRead(Constants::kDistanceSensorReadPin));
	if (volts == 0)
	{
		DEBUG_PRINTLN("Distance volts were 0");
		return -1;
	}
	float distance = (Constants::kDistanceCalculationA / (volts)) + Constants::kDistanceCalculationB;
	DEBUG_PRINTF("Distance volts = %d, dist * 10000 = %06ld\n", static_cast<int>(volts), static_cast<long>(distance * 10000));
	return distance;
}

int DistanceSensorManager::get_amount()
{
	return Constants::kCountDistanceSensors;
}
