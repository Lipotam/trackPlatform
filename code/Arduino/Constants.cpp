#include "Constants.h"

Constants::Constants()
{
	bluetooth_RX = 50;
	bluetooth_TX = 51;
	bluetooth_serial_speed = 9600;

	wifi_RX = 18;
	wifi_TX = 19;
	wifi_serial_speed = 115200;

	left_engine_straight_pin = 8;
	left_engine_reverse_pin = 9;
	right_engine_straight_pin = 10;
	right_engine_reverse_pin = 11;

	distance_ir_an = 0;

	line_sensor_pin = 14;
}


Constants::~Constants()
{
}


