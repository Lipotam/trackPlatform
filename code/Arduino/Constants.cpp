#include "Constants.h"

Constants::Constants()
{
	bluetooth_RX = 50;
	bluetooth_TX = 51;
	bluetooth_serial_speed = 9600;

	wifi_RX = 30;
	wifi_TX = 31;
	wifi_serial_speed = 9600;

	left_engine_enable = 7;
	left_engine_straight_pin = 8;
	left_engine_reverse_pin = 9;
	right_engine_straight_pin = 10;
	right_engine_reverse_pin = 11;
	right_engine_enable = 12;

	/*distance_sensor_read_pin = A0;*/
	distance_sensor_a_pin = 4;
	distance_sensor_b_pin = 5;
	distance_sensor_c_pin = 6;

	//line_sensor_read_pin = A1;
	line_sensor_a_pin = 15;
	line_sensor_b_pin = 16;
	line_sensor_c_pin = 17;

	servo_horizontal_pin = 34;
	servo_vertical_pin = 35;
}


Constants::~Constants()
{
}


