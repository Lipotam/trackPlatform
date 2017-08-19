#include <stdarg.h>
#include "../Constants.h"
#include "DebugSerial.h"

#ifdef DEBUG_ON

HardwareSerial* DebugSerial::serial = &Serial1;
bool DebugSerial::isInited = false;

SoftwareSerial* DebugSerial::generateDbgSerial()
{
	SoftwareSerial* serialPtr = new SoftwareSerial(Constants::dbg_uart_RX, Constants::dbg_uart_TX);
	serialPtr->begin(Constants::dbg_uart_speed);
	serialPtr->listen();
	return serialPtr;
}

DebugSerial::DebugSerial(): ConnectingDevice(serial)
{
	if (!isInited)
	{
		isInited = true;
		serial->begin(Constants::dbg_uart_speed);
	}
}

Stream* DebugSerial::getSerial()
{
	return serial;
}

void DebugSerial::send(String data)
{
	device->println(data);
}

void DebugSerial::print(String data)
{
	device->print(data);
}

void DebugSerial::println(String data)
{
	device->println(data);
}

void DebugSerial::printHex(String data)
{
	for (unsigned int i = 0; i < data.length(); ++i)
	{
		printf("%02X ", data[i]);
	}
}

void DebugSerial::printlnHex(String data)
{
	printHex(data);
	device->println("");
}

void DebugSerial::printf(const char* format, ...)
{
	char buf[printfBuffSize] = {0};
	va_list ap;
	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
	for (char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
	{
		if (*p == '\n')
			device->write('\r');
		device->write(*p);
	}
	va_end(ap);
}

#endif
