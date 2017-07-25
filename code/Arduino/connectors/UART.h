#pragma once
#include "ConnectingDevice.h"

class UART : public ConnectingDevice
{
public:
	UART(int rx, int tx, int baudrate);
	~UART();
};
