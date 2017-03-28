#pragma once
class Constants
{
public:
	/* Binded for Arduino Mega */
	int bluetooth_RX;
	int bluetooth_TX;
	int bluetooth_serial_speed;

	int wifi_RX;
	int wifi_TX;
	int wifi_serial_speed;

	Constants();
	~Constants();
};

