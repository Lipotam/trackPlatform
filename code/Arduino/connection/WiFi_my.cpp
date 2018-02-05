#include "WiFi_my.h"
#include "../utils/Timer.h"
#include "DebugSerial.h"

WiFi_my::WiFi_my(unsigned long speed) :IConnector(&Serial2) {
	//Добавить вывод IP
	DEBUG_PRINTLN("Constructor wifi");
	if (is_inited_)
	{
		return;
	}
	is_inited_ = true;
	Serial2.begin(speed);

	connect_to_module();
}

void WiFi_my::connect_to_module()
{
	is_connected_ = true;

	//TODO

	is_connected_ = false;
}

bool WiFi_my::is_need_to_read_message() {
	return is_connected_ && device_->available();
}

void WiFi_my::write_answer(uint8_t* answer_ptr, int length) {
	if (!length || !is_connected_) {
		return;
	}

	uint8_t buffer_ptr[BUFFER_SIZE];
	int buffer_length = 0;

	for (int i = 0; i < length && buffer_length < (BUFFER_SIZE - 1); i++, buffer_length++)
	{
		switch (answer_ptr[i])
		{
		case 10:
			buffer_ptr[buffer_length] = 10;
			buffer_length++;
			buffer_ptr[buffer_length] = 10;
			break;
		case 13:
			buffer_ptr[buffer_length] = 10;
			buffer_length++;
			buffer_ptr[buffer_length] = 11;
			break;
		default:
			buffer_ptr[buffer_length] = answer_ptr[i];
			break;
		}
	}

	IConnector::write_answer(buffer_ptr, buffer_length);
}

int WiFi_my::read_message(uint8_t* pointer, int max_length)
{
	if (!is_connected_ || !max_length)
	{
		return 0;
	}

	bool is_escaped = false;
	int answer_length = 0;
	uint8_t buffer_ptr[BUFFER_SIZE];
	const int buffer_length = device_->readBytesUntil(13, buffer_ptr, BUFFER_SIZE);
	
	for (int buffer_i = 0; answer_length < max_length && buffer_i < buffer_length; answer_length++, buffer_i++)
	{
		if (is_escaped)
		{
			is_escaped = false;
			switch (buffer_ptr[buffer_i])
			{
			case 10:
				pointer[answer_length] = 10;
				break;
			case 11:
				pointer[answer_length] = 13;
			default:
				DEBUG_PRINTLN("Escape parsing error from Wi-Fi");
				return -1;
			}
		}
		else
		{
			switch (buffer_ptr[buffer_i])
			{
			case 10:
				is_escaped = true;
				answer_length--;
				break;
			case 13:
				return answer_length;
			default:
				pointer[answer_length] = buffer_ptr[buffer_i];
				break;
			}
		}
	}

	return answer_length;
}
