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
#if (LINE_SENSOR_REV == 1)

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

#elif (LINE_SENSOR_REV == 2)

	switch (number) {
	case 1:
		digitalWrite(Constants::kLineSensorAPin, LOW);
		digitalWrite(Constants::kLineSensorBPin, LOW);
		digitalWrite(Constants::kLineSensorCPin, HIGH);
		break;
	case 2:
		digitalWrite(Constants::kLineSensorAPin, HIGH);
		digitalWrite(Constants::kLineSensorBPin, LOW);
		digitalWrite(Constants::kLineSensorCPin, HIGH);
		break;
	case 3:
		digitalWrite(Constants::kLineSensorAPin, LOW);
		digitalWrite(Constants::kLineSensorBPin, HIGH);
		digitalWrite(Constants::kLineSensorCPin, HIGH);
		break;
	case 4:
		digitalWrite(Constants::kLineSensorAPin, HIGH);
		digitalWrite(Constants::kLineSensorBPin, HIGH);
		digitalWrite(Constants::kLineSensorCPin, HIGH);
		break;
	case 5:
		digitalWrite(Constants::kLineSensorAPin, HIGH);
		digitalWrite(Constants::kLineSensorBPin, HIGH);
		digitalWrite(Constants::kLineSensorCPin, LOW);
		break;
	default:
		break;
	}

	delay(1);
#else

#error Line sensor revisions 1 or 2 are supported only

#endif
}

int LineSensorManager::get_sensor_value(int number) {
	return (get_raw_sensor_value(number) > static_cast<int>(Constants::kMinimalLineBound)) ? 1 : 0;
}

int LineSensorManager::get_raw_sensor_value(int number)
{
	DEBUG_PRINTF("Get line raw value from sensor %d\n", number);
	choose_sensor(number);
	return analogRead(Constants::kLineSensorReadPin);
}

int LineSensorManager::get_amount()
{
	return Constants::kCountLineSensors;
}
