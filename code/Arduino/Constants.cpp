#include "Constants.h"

/* Bluetooth */
const uint8_t Constants::bluetooth_RX = 50;
const uint8_t Constants::bluetooth_TX = 51;
const uint32_t Constants::bluetooth_serial_speed = 9600;

/* Wi-fi */
const uint8_t Constants::wifi_RX = 30;
const uint8_t Constants::wifi_TX = 31;
const uint32_t Constants::wifi_serial_speed = 9600;

/* Movement controller (L298N) */
const uint8_t Constants::left_engine_enable = A8;
const uint8_t Constants::left_engine_straight_pin = 30;
const uint8_t Constants::left_engine_reverse_pin = 31;
const uint8_t Constants::right_engine_straight_pin = 32;
const uint8_t Constants::right_engine_reverse_pin = 33;
const uint8_t Constants::right_engine_enable = A9;

/* Distanse controller */
const uint8_t Constants::distance_sensor_read_pin = A0;
const uint8_t Constants::distance_sensor_a_pin = 4;
const uint8_t Constants::distance_sensor_b_pin = 5;
const uint8_t Constants::distance_sensor_c_pin = 6;

/* Line controller */
const uint8_t Constants::line_sensor_read_pin = A1;
const uint8_t Constants::line_sensor_a_pin = 15;
const uint8_t Constants::line_sensor_b_pin = 16;
const uint8_t Constants::line_sensor_c_pin = 17;

/* Servo controller */
const uint8_t Constants::servo_horizontal_pin = 34;
const uint8_t Constants::servo_vertical_pin = 35;

const char Constants::commands_delimetr = ';';

/* Class constants */
const uint8_t Constants::min_speed = 0;
const uint8_t Constants::max_speed = 255;
const uint16_t Constants::servo_delay = 20;

const uint8_t Constants::countDistanceSensors = 5;
const uint8_t Constants::countLineSensors = 5;
const uint16_t Constants::minimalLineBound = 270;

Constants::Constants()
{
}

Constants::~Constants()
{
}
