#pragma once
#include <SoftwareSerial.h>

#include "ConnectingDevice.h"

class DebugSerial : ConnectingDevice
{
	static SoftwareSerial* serial;

	static SoftwareSerial* generateDbgSerial();
public:
	DebugSerial();

	static Stream* getSerial();
};
