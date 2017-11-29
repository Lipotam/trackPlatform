#include <SoftwareSerial.h>

#include "../config/Constants.h"
#include "IConnector.h"

IConnector::IConnector(Stream* ptr) : device(ptr)
{
	device->setTimeout(Constants::commands_wait_time);
}

IConnector::IConnector(int rx, int tx, unsigned long speed)
{
	SoftwareSerial* serialPtr = new SoftwareSerial(rx, tx);
	serialPtr->begin(speed);
	serialPtr->listen();

	device = serialPtr;
	device->setTimeout(Constants::commands_wait_time);
}

void IConnector::write_answer(String answer)
{
	device->print(answer);
}

bool IConnector::is_need_to_read_message()
{
	return device->available();
}

int IConnector::read_message(uint8_t* pointer, int max_length)
{
	return device->readBytes(pointer, max_length);
}


IConnector::~IConnector()
{
}
