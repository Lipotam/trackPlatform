#pragma once
#include <Arduino.h>
#include <Stream.h>

class IConnector
{
protected:
	explicit IConnector(Stream* ptr);

	Stream *device;
public:
	IConnector(int rx, int tx, unsigned long speed);
	virtual ~IConnector();

	virtual bool is_need_to_read_message();
	virtual String read_message();
	virtual void write_answer(String answer);
};

