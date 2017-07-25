#include "UART.h"

UART::UART(int rx, int tx, int baudrate): ConnectingDevice(rx, tx, baudrate)
{
}

UART::~UART()
{
}
