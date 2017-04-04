#include "Constants.h"

Constants::Constants()
{
	bluetooth_RX = 50;
	bluetooth_TX = 51;
	bluetooth_serial_speed = 9600;

	wifi_RX = 18;
	wifi_TX = 19;
	wifi_serial_speed = 115200;

	left_engine_1 = 8;
	left_engine_2 = 9;
	right_engine_1 = 10;
	right_engine_2 = 11;

	distance_ir_an = 0;

	line_1 = 14;
}


Constants::~Constants()
{
}


