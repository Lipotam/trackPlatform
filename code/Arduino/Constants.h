#pragma once 
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

	int distance_ir_an;

	int line_sensor_pin;

	Constants();
	~Constants();
};

