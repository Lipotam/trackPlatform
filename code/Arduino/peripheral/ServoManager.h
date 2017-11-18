#pragma once
#include <Servo.h>

/**
 * @brief Servo controller for 2 axes: X & Y
 * @attention Create only one object of that class. And create it in setup() method only
 */
class ServoManager
{
	Servo horizontal_servo;
	Servo vertical_servo;

	void init();
	Servo* convert_servo_id(const ServoIndex servo_id);

public:
	ServoManager();
	~ServoManager();

	int get_servo_degree(ServoIndex servo_id);
	void set_servo_degree(ServoIndex servo_id, int degree);
};

