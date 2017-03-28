#include "Bluetooth.h"


Bluetooth::Bluetooth() : ConnectingDevice(constants.bluetooth_RX, constants.bluetooth_TX, constants.bluetooth_serial_speed)
{
}


Bluetooth::~Bluetooth()
{
}
