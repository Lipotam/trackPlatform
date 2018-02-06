#pragma once
#include <Arduino.h>

class Constants
{
public:
	// static const uint8_t bluetooth_RX;
	// static const uint8_t bluetooth_TX;
	static const uint32_t kBluetoothSerialSpeed;

	// static const uint8_t wifi_RX;
	// static const uint8_t wifi_TX;
	static const uint32_t kWifiSerialSpeed;
	static const uint32_t kWifiHandshakeWaitMs;

	// static const uint8_t usb_RX;
	// static const uint8_t usb_TX;
	static const uint32_t kUsbSerialSpeed;

	//static const uint8_t dbg_uart_RX;
	//static const uint8_t dbg_uart_TX;
	static const uint32_t kDbgUartSpeed;

	static const uint8_t kLeftEngineEnable;
	static const uint8_t kLeftEngineStraightPin;
	static const uint8_t kLeftEngineReversePin;
	static const uint8_t kRightEngineStraightPin;
	static const uint8_t kRightEngineReversePin;
	static const uint8_t kRightEngineEnable;

	static const uint8_t kDistanceSensorReadPin;
	static const uint8_t kDistanceSensorAPin;
	static const uint8_t kDistanceSensorBPin;
	static const uint8_t kDistanceSensorCPin;

	static const uint8_t kLineSensorReadPin;
	static const uint8_t kLineSensorAPin;
	static const uint8_t kLineSensorBPin;
	static const uint8_t kLineSensorCPin;

	static const uint8_t kServoHorizontalPin;
	static const uint8_t kServoVerticalPin;

	static const char kCommandsDelimetr;
	static const char kCommandsStopSymbol;
	static const uint32_t kCommandsWaitTime;

	static const uint8_t kMinSpeed;
	static const uint8_t kMaxSpeed;
	static const uint16_t kServoDelay;

	static const uint8_t kCountDistanceSensors;
	static const int16_t kSensorDelay;

	static const uint8_t kCountLineSensors;
	static const uint16_t kMinimalLineBound;

	static const uint32_t kWaitCommandTimeInMs;

	static const String kGoodAnswer;
	static const String kBadAnswer;

	Constants();
	~Constants();
};

