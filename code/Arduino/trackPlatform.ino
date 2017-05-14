#include <Servo.h>
#include <Wire.h>
#include "Constants.h"
#include "ConnectingDevice.h"
#include "Bluetooth.h"
#include "WiFi.h"
#include "SoftwareSerial.h"
#include "CommandsController.h"
#include "SensorsController.h"
#include "ServoController.h"

Constants constants;
Bluetooth bluetooth(constants.bluetooth_RX, constants.bluetooth_TX, constants.bluetooth_serial_speed);
WiFi wifi(constants.wifi_RX, constants.wifi_TX, constants.wifi_serial_speed);
ConnectingDevice *device;
CommandsController controller;


bool connected = false;

void setup()
{
	Serial.begin(9600);
	
	while (!connected) {
		if (bluetooth.isActive()) {
			connected = true;
			device = &bluetooth;
		}
		else if (wifi.isActive()) {
			connected = true;
			device = &wifi;
		}
	}
}

void loop()
{
	delay(100);
	controller.handle(device, device->read());
}
