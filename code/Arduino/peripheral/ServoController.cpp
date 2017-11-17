#include "../CommandsEnum.h"
#include "../connectors/DebugSerial.h"
#include "ServoController.h"

ServoController::ServoController()
{
	init();
}

void ServoController::init() {
	horizontal_servo.attach(constants.servo_horizontal_pin);
	vertical_servo.attach(constants.servo_vertical_pin);

	set_servo_degree(xy_plane, 0);
	set_servo_degree(xz_plane, 0);
}

Servo* ServoController::convert_servo_id(const ServoIndex servo_id)
{
	if (servo_id == xy_plane)
	{
		return &horizontal_servo;
	}
	if (servo_id == xz_plane)
	{
		return &vertical_servo;
	}

	DEBUG_PRINTF("Bad servo index: %d", servo_id);
	return &vertical_servo;
}

ServoController::~ServoController()
{
}

int ServoController::get_servo_degree(ServoIndex servo_id)
{
	DEBUG_PRINTF("Get %d servo angle\n", servo_id);
	return convert_servo_id(servo_id)->read();
}

void ServoController::set_servo_degree(ServoIndex servo_id, int degree)
{
	DEBUG_PRINTF("Set %d servo to angle %d\n", servo_id, degree);
	convert_servo_id(servo_id)->write(degree);
	delay(constants.servo_delay);
}
