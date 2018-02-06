#pragma once
#include <Arduino.h>
#include <Stream.h>

#define BUFFER_SIZE 64

class IConnector
{
protected:
	explicit IConnector(Stream* ptr);

	Stream *device_;
public:
	IConnector(int rx, int tx, unsigned long speed);
	virtual ~IConnector();

	virtual bool is_need_to_read_message();
	virtual int read_message(uint8_t* pointer, int max_length);
	virtual void write_answer(const uint8_t* answer_ptr, int length);
};

