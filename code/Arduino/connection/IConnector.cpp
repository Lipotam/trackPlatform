#include <SoftwareSerial.h>

#include "../config/Constants.h"
#include "IConnector.h"

IConnector::IConnector(Stream* ptr) : device_(ptr)
{
	device_->setTimeout(Constants::kCommandsWaitTime);
}

IConnector::IConnector(int rx, int tx, unsigned long speed)
{
	SoftwareSerial* serial_ptr = new SoftwareSerial(rx, tx);
	serial_ptr->begin(speed);
	serial_ptr->listen();

	device_ = serial_ptr;
	device_->setTimeout(Constants::kCommandsWaitTime);
}

void IConnector::write_answer(uint8_t* answer_ptr, int length)
{
	for (int i = 0; i < length; ++i)
	{
		device_->print((reinterpret_cast<char*>(answer_ptr))[i]);
	}
}

bool IConnector::is_need_to_read_message()
{
	return device_->available();
}

int IConnector::read_message(uint8_t* pointer, int max_length)
{
	return device_->readBytes(pointer, max_length);
}


IConnector::~IConnector()
{
}
