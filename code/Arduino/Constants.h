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

	int left_engine_1;
	int left_engine_2;
	int right_engine_1;
	int right_engine_2;

	Constants();
	~Constants();
};

