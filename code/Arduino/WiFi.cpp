#include "WiFi.h"



WiFi::WiFi() : ConnectingDevice(constants.wifi_RX, constants.wifi_TX, constants.wifi_serial_speed)
{
}


WiFi::~WiFi()
{
}
