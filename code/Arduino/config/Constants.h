#pragma once
#include <Arduino.h>
#include "ImageConfiguration.h"

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

	static const uint8_t kDisplayDcPin;
	static const uint8_t kDisplayCsPin;
	static const uint8_t kDisplayResetPin;

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

	static const ImageConfiguration kUsbImageConfiguration;
	static const ImageConfiguration kBluetoothImageConfiguration;
	static const ImageConfiguration kWifiImageConfiguration;
	static const ImageConfiguration kStatusImageConfiguration;
	static const ImageConfiguration kLineImageConfiguration;
	static const ImageConfiguration kPrintAreaImageConfiguration;

	static const uint8_t* kUsbImage;
	static const uint8_t* kBluetoothImage;
	static const uint8_t* kWifiImage;
	static const uint8_t* const* kStatusImages;
	static const uint8_t kStatusImagesNum;

	static const uint8_t* kDisplayTogglePins;
	static const uint8_t kDisplayTogglePinAmount;

	static const String kBluetoothHeader;
	static const String kBluetoothAp;
	static const String kBluetoothPassword;

	static const String kWifiHeader;
	static const String kWifiAp;
	static const String kWifiPassword;
	static const String kWifiIp;

	static const String kDebugHeader;

	static const String kHardwareInfoHeader;

	Constants();
	~Constants();
};

