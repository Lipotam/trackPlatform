#include "Constants.h"

/* Bluetooth (Hardware Serial3) */
// const uint8_t Constants::bluetooth_RX = 15;
// const uint8_t Constants::bluetooth_TX = 14;
const uint32_t Constants::kBluetoothSerialSpeed = 9600;

/* Wi-fi (Hardware Serial2) */
// const uint8_t Constants::wifi_RX = 17;
// const uint8_t Constants::wifi_TX = 16;
const uint32_t Constants::kWifiSerialSpeed = 115200;

/* USB (Hardware Serial) */
// const uint8_t Constants::usb_RX = 0;
// const uint8_t Constants::usb_TX = 1;
const uint32_t Constants::kUsbSerialSpeed = 9600;

/* Debug serial (Hardware Serial1) */
//const uint8_t Constants::dbg_uart_RX = 19;
//const uint8_t Constants::dbg_uart_TX = 18;
const uint32_t Constants::kDbgUartSpeed = 9600;

/* Movement controller (L298N) */
const uint8_t Constants::kLeftEngineEnable = 10;
const uint8_t Constants::kLeftEngineStraightPin = 30;
const uint8_t Constants::kLeftEngineReversePin = 31;
const uint8_t Constants::kRightEngineStraightPin = 32;
const uint8_t Constants::kRightEngineReversePin = 33;
const uint8_t Constants::kRightEngineEnable = 11;

/* Distanse controller */
const uint8_t Constants::kDistanceSensorReadPin = A2;
const uint8_t Constants::kDistanceSensorAPin = 4;
const uint8_t Constants::kDistanceSensorBPin = 5;
const uint8_t Constants::kDistanceSensorCPin = A3;

/* Line controller */
const uint8_t Constants::kLineSensorReadPin = A0;
const uint8_t Constants::kLineSensorAPin = 6;
const uint8_t Constants::kLineSensorBPin = 7;
const uint8_t Constants::kLineSensorCPin = A1;

/* Servo controller */
const uint8_t Constants::kServoHorizontalPin = 34;
const uint8_t Constants::kServoVerticalPin = 35;

const char Constants::kCommandsDelimetr = ';';
const char Constants::kCommandsStopSymbol = '|';
const uint32_t Constants::kCommandsWaitTime = 50;

/* Class constants */
const uint8_t Constants::kMinSpeed = 0;
const uint8_t Constants::kMaxSpeed = 255;
const uint16_t Constants::kServoDelay = 20;

const uint8_t Constants::kCountDistanceSensors = 5;
const int16_t Constants::kDistanceCalculationA = 6762;
const int16_t Constants::kDistanceCalculationB = -4;

const uint8_t Constants::kCountLineSensors = 5;
const uint16_t Constants::kMinimalLineBound = 270;

const uint32_t Constants::kWaitCommandTimeInMs = 5000;

const String Constants::kGoodAnswer = "OK";
const String Constants::kBadAnswer = "ERROR";

Constants::Constants()
{
}

Constants::~Constants()
{
}
