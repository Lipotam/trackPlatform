#pragma once
#include <Arduino.h>
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>

#include "../connection/ConnectorEnum.h"
#include "../management/ProcessingStatusEnum.h"
#include "DisplayStateEnum.h"

class DisplayManager
{
public:
	DisplayManager();

	/**
	 * @brief Manual display repainting
	 */
	void repaint();

	void set_connector(ConnectorEnum connector_index);
	void reset_connector();

	void set_status(ProcessingStatusEnum status);

	void print_debug_string(String info);

private:
	static const int kUsbIconXPos = 0;
	static const int kUsbIconYPos = 0;
	static const int kBluetoothIconXPos = 0;
	static const int kBluetoothIconYPos = 16;
	static const int kWiFiIconXPos = 0;
	static const int kWiFiIconYPos = 32;
	static const int kStatusIconXPos = 0;
	static const int kStatusIconYPos = 48;

	bool info_changed_ = true;
	DisplayStateEnum current_state_ = hardware_display_state;
	ConnectorEnum current_connector_ = usb;
	bool is_connector_setted_ = false;
	ProcessingStatusEnum current_status_ = ProcessingStatusEnum::success;

	void print_icons();

	void print_bluetooth_info();
	void print_wifi_info();
	void print_hardware_info();
	void print_debug_info();
};
