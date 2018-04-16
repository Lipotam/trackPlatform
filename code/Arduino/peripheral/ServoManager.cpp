#include "../config/CommandsEnum.h"
#include "../connection/DebugSerial.h"
#include "../config/Constants.h"
#include "ServoManager.h"

ServoManager::ServoManager()
{
	init();
}

void ServoManager::init() {
	horizontal_servo.attach(Constants::kServoHorizontalPin);
	vertical_servo.attach(Constants::kServoVerticalPin);

	set_servo_degree(xy_plane, 0);
	set_servo_degree(xz_plane, 0);
}

Servo* ServoManager::convert_servo_id(const ServoIndex servo_id)
{
	if (servo_id == xy_plane)
	{
		return &horizontal_servo;
	}
	if (servo_id == xz_plane)
	{
		return &vertical_servo;
	}

	DEBUG_PRINTF("Bad servo index: %d\n", servo_id);
	return &vertical_servo;
}

ServoManager::~ServoManager()
{
}

int ServoManager::get_servo_degree(ServoIndex servo_id)
{
	DEBUG_PRINTF("Get %d servo angle\n", servo_id);
	return convert_servo_id(servo_id)->read();
}

void ServoManager::set_servo_degree(ServoIndex servo_id, int degree)
{
	DEBUG_PRINTF("Set %d servo to angle %d\n", servo_id, degree);
	convert_servo_id(servo_id)->write(degree);
	delay(Constants::kServoDelay);
}
