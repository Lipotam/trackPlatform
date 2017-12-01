#include <stdarg.h>
#include "../config/Constants.h"
#include "DebugSerial.h"

#ifdef DEBUG_ON

HardwareSerial* DebugSerial::serial_ = &Serial1;
bool DebugSerial::isInited = false;

DebugSerial::DebugSerial(): IConnector(serial_)
{
	if (!isInited)
	{
		isInited = true;
		serial_->begin(Constants::kDbgUartSpeed);
	}
}

Stream* DebugSerial::get_serial()
{
	return serial_;
}

void DebugSerial::write_answer(String data)
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
