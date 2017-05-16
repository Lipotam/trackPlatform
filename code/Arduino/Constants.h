#pragma once 
#include <stdint.h>

class Constants
{
public:
	int bluetooth_RX;
	int bluetooth_TX;
	int bluetooth_serial_speed;

	int wifi_RX;
	int wifi_TX;
	int wifi_serial_speed;

	int left_engine_straight_pin;
	int left_engine_reverse_pin;
	int right_engine_straight_pin;
	int right_engine_reverse_pin;

	int left_engine_enable;
	int right_engine_enable;

	long  distance_sensor_read_pin;
	int distance_sensor_a_pin;
	int distance_sensor_b_pin;
	int distance_sensor_c_pin;
	

	long  line_sensor_read_pin;
	int line_sensor_a_pin;
	int line_sensor_b_pin;
	int line_sensor_c_pin;
	
	int servo_horizontal_pin;
	int servo_vertical_pin;

	char commands_delimetr;

	Constants();
	~Constants();
};

