#include "../CommandsEnum.h"
#include "../connectors/DebugSerial.h"
#include "SensorsController.h"

SensorsController::SensorsController()
{
	countDistanceSensors = constants.countDistanceSensors;
	countLineSensors = constants.countLineSensors;
	minimalLineBound = constants.minimalLineBound;

	pinMode(constants.line_sensor_a_pin, OUTPUT);
	pinMode(constants.line_sensor_b_pin, OUTPUT);
	pinMode(constants.line_sensor_c_pin, OUTPUT);

	pinMode(constants.distance_sensor_a_pin, OUTPUT);
	pinMode(constants.distance_sensor_b_pin, OUTPUT);
	pinMode(constants.distance_sensor_c_pin, OUTPUT);

	digitalWrite(constants.line_sensor_a_pin, HIGH);
	digitalWrite(constants.line_sensor_b_pin, LOW);
	digitalWrite(constants.line_sensor_c_pin, HIGH);
}


void SensorsController::exec(ConnectingDevice *device, String command) {
	int *arr = nullptr;
	switch (command[1])
	{
	case distance_sensor:
		device->send(String(getDistance(parse_command(command, 2, command.length()))));
		break;
	case distance_sensor_all:
		device->send(intArrayToString(arr = getDistanceAll(), countDistanceSensors));
		break;
	case line_sensor:
		device->send(String(getLine(parse_command(command, 2, command.length()))));
		break;
	case line_sensor_all:
		device->send(intArrayToString(arr = getLineAll(), countLineSensors));
		break;
	default:
		break;
	}
	if (arr)
	{
		delete[] arr;
	}
}

void SensorsController::chooseLineSensor(int number) {
	switch (number) {
		case 1:
			digitalWrite(constants.line_sensor_a_pin, LOW);
			digitalWrite(constants.line_sensor_b_pin, LOW);
			digitalWrite(constants.line_sensor_c_pin, HIGH);
			break;
		case 2:
			digitalWrite(constants.line_sensor_a_pin, HIGH);
			digitalWrite(constants.line_sensor_b_pin, HIGH);
			digitalWrite(constants.line_sensor_c_pin, HIGH);
			break;
		case 3:
			digitalWrite(constants.line_sensor_a_pin, HIGH);
			digitalWrite(constants.line_sensor_b_pin, LOW);
			digitalWrite(constants.line_sensor_c_pin, HIGH);
			break;
		case 4:
			digitalWrite(constants.line_sensor_a_pin, LOW);
			digitalWrite(constants.line_sensor_b_pin, HIGH);
			digitalWrite(constants.line_sensor_c_pin, HIGH);
			break;
		case 5:
			digitalWrite(constants.line_sensor_a_pin, HIGH);
			digitalWrite(constants.line_sensor_b_pin, LOW);
			digitalWrite(constants.line_sensor_c_pin, LOW);
			break;
		default:
			break;
	}
}

int SensorsController::getLine(int number) {
	chooseLineSensor(number);
	return analogRead(constants.line_sensor_read_pin) > minimalLineBound  ? 1 : 0;
}

int* SensorsController::getLineAll() {
	int* arr = new int[countLineSensors];
	for (int i = 0; i < countLineSensors; i++) {
		arr[i] = getLine(i + 1);
	}
	return arr;
}

void SensorsController::chooseDistanceSensor(int number) {
	switch (number) {
		case 1:
			digitalWrite(constants.distance_sensor_a_pin, HIGH);
			digitalWrite(constants.distance_sensor_b_pin, LOW);
			digitalWrite(constants.distance_sensor_c_pin, LOW);
			break;
		case 2:
			digitalWrite(constants.distance_sensor_a_pin, LOW);
			digitalWrite(constants.distance_sensor_b_pin, HIGH);
			digitalWrite(constants.distance_sensor_c_pin, HIGH);
			break;
		case 3:
			digitalWrite(constants.distance_sensor_a_pin, LOW);
			digitalWrite(constants.distance_sensor_b_pin, LOW);
			digitalWrite(constants.distance_sensor_c_pin, HIGH);
			break;
		case 4:
			digitalWrite(constants.distance_sensor_a_pin, HIGH);
			digitalWrite(constants.distance_sensor_b_pin, LOW);
			digitalWrite(constants.distance_sensor_c_pin, HIGH);
			break;
		case 5:
			digitalWrite(constants.distance_sensor_a_pin, HIGH);
			digitalWrite(constants.distance_sensor_b_pin, HIGH);
			digitalWrite(constants.distance_sensor_c_pin, HIGH);
			break;
		default:
			break;
   }
}


int SensorsController::getDistance(int number) {
	chooseDistanceSensor(number);
	float volts = analogRead(constants.distance_sensor_read_pin);
	DebugSerial::getSerial()->printf("Distance volts: %d\n", (int)volts);
	if (volts == 0)
	{
		DebugSerial::getSerial()->println("Distance volts were 0");
		return -1;				//TODO: crutch
	}
	float distance = (6762 / (volts)) - 4;
	return distance;
}

int* SensorsController::getDistanceAll() {
	int* arr = new int[countDistanceSensors];
	for (int i = 0; i < countDistanceSensors; i++) {
		arr[i] = getDistance(i + 1);
	}
	return arr;
}

int SensorsController::getAverageDistance(int number, int n) {
	int* arr = getDistanceNTime(number, n);
	int averageDistance = 0;
	for (int i = 0; i < n; i++) {
		averageDistance += arr[i];
	}
	delete[] arr;
	return averageDistance / n;
}


int* SensorsController::getDistanceNTime(int number, int n) {
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = getDistance(number);
	}
	return arr;
}

SensorsController::~SensorsController()
{
}
