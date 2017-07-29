#pragma once
#include <SoftwareSerial.h>

#include "ConnectingDevice.h"

class DebugSerial : public ConnectingDevice
{
	static SoftwareSerial* serial;

	static SoftwareSerial* generateDbgSerial();
public:
	DebugSerial();

	static Stream* getSerial();

	void send(String data) override;
};
