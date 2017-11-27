#include "Constants.h"

/* Bluetooth (Hardware Serial3) */
// const uint8_t Constants::bluetooth_RX = 15;
// const uint8_t Constants::bluetooth_TX = 14;
const uint32_t Constants::bluetooth_serial_speed = 9600;

/* Wi-fi (Hardware Serial2) */
// const uint8_t Constants::wifi_RX = 17;
// const uint8_t Constants::wifi_TX = 16;
const uint32_t Constants::wifi_serial_speed = 115200;

/* USB (Hardware Serial) */
// const uint8_t Constants::usb_RX = 0;
// const uint8_t Constants::usb_TX = 1;
const uint32_t Constants::usb_serial_speed = 9600;

/* Debug serial (Hardware Serial1) */
//const uint8_t Constants::dbg_uart_RX = 19;
//const uint8_t Constants::dbg_uart_TX = 18;
const uint32_t Constants::dbg_uart_speed = 9600;

/* Movement controller (L298N) */
const uint8_t Constants::left_engine_enable = 10;
const uint8_t Constants::left_engine_straight_pin = 30;
const uint8_t Constants::left_engine_reverse_pin = 31;
const uint8_t Constants::right_engine_straight_pin = 32;
const uint8_t Constants::right_engine_reverse_pin = 33;
const uint8_t Constants::right_engine_enable = 11;

/* Distanse controller */
const uint8_t Constants::distance_sensor_read_pin = A2;
const uint8_t Constants::distance_sensor_a_pin = 4;
const uint8_t Constants::distance_sensor_b_pin = 5;
const uint8_t Constants::distance_sensor_c_pin = A3;

/* Line controller */
const uint8_t Constants::line_sensor_read_pin = A0;
const uint8_t Constants::line_sensor_a_pin = 6;
const uint8_t Constants::line_sensor_b_pin = 7;
const uint8_t Constants::line_sensor_c_pin = A1;

/* Servo controller */
const uint8_t Constants::servo_horizontal_pin = 34;
const uint8_t Constants::servo_vertical_pin = 35;

const char Constants::commands_delimetr = ';';
const char Constants::commands_stop_symbol = '|';
const uint32_t Constants::commands_wait_time = 100;

/* Class constants */
const uint8_t Constants::min_speed = 0;
const uint8_t Constants::max_speed = 255;
const uint16_t Constants::servo_delay = 20;

const uint8_t Constants::count_distance_sensors = 5;
const int16_t Constants::distance_calculation_a = 6762;
const int16_t Constants::distance_calculation_b = -4;

const uint8_t Constants::count_line_sensors = 5;
const uint16_t Constants::minimal_line_bound = 270;

const uint32_t Constants::wait_command_time_in_ms = 2000000;

const String Constants::good_answer = "OK";
const String Constants::bad_answer = "ERROR";

Constants::Constants()
{
}

Constants::~Constants()
{
}
