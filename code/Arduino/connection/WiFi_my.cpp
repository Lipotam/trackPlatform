#include "WiFi_my.h"
#include "../utils/Timer.h"
#include "DebugSerial.h"
#include "../config/Constants.h"

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

bool WiFi_my::is_module_connected() const
{
	return is_connected_;
}

bool WiFi_my::is_message_was_read_before_timeout(Timer& timer, const String& to_compare)
{
	is_connected_ = true;

	while (!(is_need_to_read_message() && is_message_equal(to_compare)))
	{
		if (timer.isFinished())
		{
			is_connected_ = false;
			return false;
		}
		delay(100);
	}
	is_connected_ = false;
	return true;
}

bool WiFi_my::is_message_equal(const String& to_compare)
{
	uint8_t buffer[BUFFER_SIZE] = { 0 };
	int length = read_message(buffer, sizeof(buffer));

	//TODO
	return false;
}

void WiFi_my::connect_to_module()
{
	const String require_request("I'm ready, Milord!");
	const String require_second_request("Yes, Sir");
	const char responce[] = "Sir";
	const int delay_ms = 100;

	Timer timer(Constants::kWifiHandshakeWaitMs);
	timer.start_or_resume();

	if (!is_message_was_read_before_timeout(timer, require_request))
	{
		return;
	}

	write_answer(reinterpret_cast<const uint8_t*>(responce), sizeof(responce));

	if (!is_message_was_read_before_timeout(timer, require_second_request))
	{
		return;
	}

	is_connected_ = true;
}

bool WiFi_my::is_need_to_read_message() {
	return is_connected_ && device_->available();
}

void WiFi_my::write_answer(const uint8_t* answer_ptr, int length) {
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
