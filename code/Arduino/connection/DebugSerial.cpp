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

void DebugSerial::write_answer(const uint8_t* answer_ptr, int length)
{
	IConnector::write_answer(answer_ptr, length);
}

void DebugSerial::print(String data)
{
	device_->print(data);
}

void DebugSerial::println(String data)
{
	device_->println(data);
}

void DebugSerial::printHex(String data)
{
	for (unsigned int i = 0; i < data.length(); ++i)
	{
		printf("%02X ", data[i]);
	}
}

void DebugSerial::printHex(uint8_t* data, size_t size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		printf("%02X ", data[i]);
	}
}

void DebugSerial::printlnHex(String data)
{
	printHex(data);
	device_->println("");
}

void DebugSerial::printlnHex(uint8_t* data, size_t size)
{
	printHex(data, size);
	device_->println("");
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
			device_->write('\r');
		device_->write(*p);
	}
	va_end(ap);
}

#endif
