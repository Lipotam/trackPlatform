#include "Constants.h"

const uint8_t Constants::bluetooth_RX = 50;
const uint8_t Constants::bluetooth_TX = 51;
const uint32_t Constants::bluetooth_serial_speed = 9600;

const uint8_t Constants::wifi_RX = 10;
const uint8_t Constants::wifi_TX = 11;
const uint32_t Constants::wifi_serial_speed = 9600;

const uint8_t Constants::left_engine_enable = 29;
const uint8_t Constants::left_engine_straight_pin = 30;
const uint8_t Constants::left_engine_reverse_pin = 31;
const uint8_t Constants::right_engine_straight_pin = 32;
const uint8_t Constants::right_engine_reverse_pin = 33;
const uint8_t Constants::right_engine_enable = 34;

const uint8_t Constants::distance_sensor_read_pin = A0;
const uint8_t Constants::distance_sensor_a_pin = 4;
const uint8_t Constants::distance_sensor_b_pin = 5;
const uint8_t Constants::distance_sensor_c_pin = 6;

const uint8_t Constants::line_sensor_read_pin = A1;
const uint8_t Constants::line_sensor_a_pin = 15;
const uint8_t Constants::line_sensor_b_pin = 16;
const uint8_t Constants::line_sensor_c_pin = 17;

const uint8_t Constants::servo_horizontal_pin = 38;
const uint8_t Constants::servo_vertical_pin = 39;

const char Constants::commands_delimetr = ';';

Constants::Constants()
{
}


Constants::~Constants()
{
}


