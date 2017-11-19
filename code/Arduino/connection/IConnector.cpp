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
	device->print(answer + Constants::commands_stop_symbol);
}

bool IConnector::is_need_to_read_message()
{
	return device->available();
}

String IConnector::read_message()
{
	return device->readStringUntil(Constants::commands_stop_symbol);
}


IConnector::~IConnector()
{
}
