#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "LineSensorManager.h"

LineSensorManager::LineSensorManager()
{
	pinMode(Constants::kLineSensorAPin, OUTPUT);
	pinMode(Constants::kLineSensorBPin, OUTPUT);
	pinMode(Constants::kLineSensorCPin, OUTPUT);
}

void LineSensorManager::choose_sensor(int number) {
	switch (number) {
		case 1:
			digitalWrite(Constants::kLineSensorAPin, LOW);
			digitalWrite(Constants::kLineSensorBPin, LOW);
			digitalWrite(Constants::kLineSensorCPin, HIGH);
			break;
		case 2:
			digitalWrite(Constants::kLineSensorAPin, HIGH);
			digitalWrite(Constants::kLineSensorBPin, HIGH);
			digitalWrite(Constants::kLineSensorCPin, HIGH);
			break;
		case 3:
			digitalWrite(Constants::kLineSensorAPin, HIGH);
			digitalWrite(Constants::kLineSensorBPin, LOW);
			digitalWrite(Constants::kLineSensorCPin, HIGH);
			break;
		case 4:
			digitalWrite(Constants::kLineSensorAPin, LOW);
			digitalWrite(Constants::kLineSensorBPin, HIGH);
			digitalWrite(Constants::kLineSensorCPin, HIGH);
			break;
		case 5:
			digitalWrite(Constants::kLineSensorAPin, HIGH);
			digitalWrite(Constants::kLineSensorBPin, LOW);
			digitalWrite(Constants::kLineSensorCPin, LOW);
			break;
		default:
			break;
	}
}

int LineSensorManager::get_sensor_value(int number) {
	DEBUG_PRINTF("Get line value from sensor %d\n", number);
	choose_sensor(number);
	return (analogRead(Constants::kLineSensorReadPin) > static_cast<int>(Constants::kMinimalLineBound)) ? 1 : 0;
}

int LineSensorManager::get_amount()
{
	return Constants::kCountLineSensors;
}
