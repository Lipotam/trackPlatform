#include "Constants.h"

/* Buffer initialisation */
namespace
{
	const uint8_t kUsbIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x0F, 0xF0, 0x08, 0x10, 0x08, 0x10, 0x0A, 0x50, 0x08, 0x10, 0x08, 0x10, 0x3F, 0xFC,
		0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x30, 0x0C, 0x10, 0x08, 0x1F, 0xF8, 0x00, 0x00
	};
	const uint8_t kBluetoothIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x01, 0x80, 0x01, 0xC0, 0x09, 0x60, 0x0D, 0x30, 0x07, 0x60, 0x03, 0xC0, 0x01, 0x80,
		0x03, 0xC0, 0x07, 0x60, 0x0D, 0x30, 0x09, 0x60, 0x01, 0xC0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
	};
	const uint8_t kWiFiIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x60, 0x00, 0x7C, 0x00, 0x07, 0x00, 0x61, 0xC0, 0x78, 0x60, 0x0E, 0x30, 0x03, 0x10,
		0x61, 0x98, 0x78, 0xC8, 0x0C, 0x4C, 0x06, 0x64, 0x62, 0x24, 0x73, 0x36, 0x73, 0x36, 0x00, 0x00
	};
	const uint8_t kStatusGoodIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70,
		0x30, 0xE0, 0x39, 0xC0, 0x1F, 0x80, 0x0F, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	const uint8_t kStatusBadIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x1E, 0x3C, 0x1F, 0x7C, 0x0F, 0xF8, 0x07, 0xF0,
		0x03, 0xE0, 0x07, 0xF0, 0x0F, 0xF8, 0x1F, 0x7C, 0x1E, 0x3C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00
	};
	const uint8_t kStatusResolvingIconBuffer[] PROGMEM = {
		0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x04, 0x30, 0x28, 0x08, 0x30, 0x04, 0x38, 0x04, 0x00, 0x04,
		0x20, 0x00, 0x20, 0x1C, 0x20, 0x0C, 0x10, 0x14, 0x0C, 0x20, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00
	};
	//const uint8_t kLineBuffer[] PROGMEM = {
	//	0x00, 0x00, 0x00, 0x00, 0x18, 0x30, 0x60, 0xFE, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00,
	//	0x00, 0x00, 0x00, 0x00, 0x0C, 0x06, 0x03, 0x3F, 0x31, 0x1B, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00
	//};

	const uint8_t* const kStatusIcons[] = {
		kStatusGoodIconBuffer,
		kStatusBadIconBuffer,
		kStatusResolvingIconBuffer
	};

	const uint8_t kDisplayPinConfig[] = {
		46, 
		47
	};
}

/* Bluetooth (Hardware Serial3) */
// const uint8_t Constants::bluetooth_RX = 15;
// const uint8_t Constants::bluetooth_TX = 14;
const uint32_t Constants::kBluetoothSerialSpeed = 9600;

/* Wi-fi (Hardware Serial2) */
// const uint8_t Constants::wifi_RX = 17;
// const uint8_t Constants::wifi_TX = 16;
const uint32_t Constants::kWifiSerialSpeed = 115200;
const uint32_t Constants::kWifiHandshakeWaitMs = 30000;

/* USB (Hardware Serial) */
// const uint8_t Constants::usb_RX = 0;
// const uint8_t Constants::usb_TX = 1;
const uint32_t Constants::kUsbSerialSpeed = 9600;

/* Debug serial (Hardware Serial1) */
//const uint8_t Constants::dbg_uart_RX = 19;
//const uint8_t Constants::dbg_uart_TX = 18;
const uint32_t Constants::kDbgUartSpeed = 9600;

/* Movement controller (L298N) */
const uint8_t Constants::kLeftEngineEnable = 11;
const uint8_t Constants::kLeftEngineStraightPin = 30;
const uint8_t Constants::kLeftEngineReversePin = 31;
const uint8_t Constants::kRightEngineStraightPin = 32;
const uint8_t Constants::kRightEngineReversePin = 33;
const uint8_t Constants::kRightEngineEnable = 10;

/* Distanse controller */
const uint8_t Constants::kDistanceSensorReadPin = A2;
const uint8_t Constants::kDistanceSensorAPin = 4;
const uint8_t Constants::kDistanceSensorBPin = 5;
const uint8_t Constants::kDistanceSensorCPin = A3;

/* Line controller */
// A = 0, B = 1, C = 2
const uint8_t Constants::kLineSensorReadPin = A0;
const uint8_t Constants::kLineSensorAPin = 6;
const uint8_t Constants::kLineSensorBPin = 7;
const uint8_t Constants::kLineSensorCPin = A1;

/* Servo controller */
const uint8_t Constants::kServoHorizontalPin = 34;
const uint8_t Constants::kServoVerticalPin = 35;

/* Display SSD1306 controller */
//const uint8_t Constants::kDisplaySpiMosiPin = 51;
//const uint8_t Constants::kDisplaySpiClkPin = 52;
const uint8_t Constants::kDisplayDcPin = 49;
const uint8_t Constants::kDisplayCsPin = 48;
const uint8_t Constants::kDisplayResetPin = -1;

const char Constants::kCommandsDelimetr = ';';
const char Constants::kCommandsStopSymbol = '|';
const uint32_t Constants::kCommandsWaitTime = 50;

/* Class constants */
const uint8_t Constants::kMinSpeed = 0;
const uint8_t Constants::kMaxSpeed = 255;
const uint16_t Constants::kServoDelay = 20;

const uint8_t Constants::kCountDistanceSensors = 5;
const int16_t Constants::kSensorDelay = 10;

const uint8_t Constants::kCountLineSensors = 5;
const uint16_t Constants::kMinimalLineBound = 270;

const uint32_t Constants::kWaitCommandTimeInMs = 5000;

const String Constants::kGoodAnswer = "OK";
const String Constants::kBadAnswer = "ERROR";

/* USB image */
const ImageConfiguration Constants::kUsbImageConfiguration =
{
	0,
	0,
	16,
	16,
};
const ImageConfiguration Constants::kBluetoothImageConfiguration =
{
	0,
	16,
	16,
	16,
};
const ImageConfiguration Constants::kWifiImageConfiguration =
{
	0,
	32,
	16,
	16,
};
const ImageConfiguration Constants::kStatusImageConfiguration =
{
	0,
	48,
	16,
	16,
};
const ImageConfiguration Constants::kLineImageConfiguration =
{
	17,
	0,
	1,
	64,
};
const ImageConfiguration Constants::kPrintAreaImageConfiguration =
{
	19,
	0,
	109,
	64,
};

const uint8_t* Constants::kUsbImage = kUsbIconBuffer;
const uint8_t* Constants::kBluetoothImage = kBluetoothIconBuffer;
const uint8_t* Constants::kWifiImage = kWiFiIconBuffer;
const uint8_t* const* Constants::kStatusImages = kStatusIcons;
const uint8_t Constants::kStatusImagesNum = sizeof(kStatusIcons) / sizeof(kStatusIcons[0]);

const uint8_t* Constants::kDisplayTogglePins = kDisplayPinConfig;
const uint8_t Constants::kDisplayTogglePinAmount = sizeof(kDisplayPinConfig) / sizeof(kDisplayPinConfig[0]);

const String Constants::kBluetoothHeader = "Bluetooth";
const String Constants::kBluetoothAp = "TrackPlatformBT";
const String Constants::kBluetoothPassword = "7777";

const String Constants::kWifiHeader = "Wi-Fi";
const String Constants::kWifiAp = "TrackPlatformWiFi";
const String Constants::kWifiPassword = "1234567890";
const String Constants::kWifiIp = "192.168.4.1";

const String Constants::kDebugHeader = "Debug";

const String Constants::kHardwareInfoHeader = "Firmware";

Constants::Constants()
{
}

Constants::~Constants()
{
}
