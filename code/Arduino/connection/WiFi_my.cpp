#include "WiFi_my.h"
#include "DebugSerial.h"
#include "../config/Constants.h"
#include "../peripheral/display/DisplayManager.h"

#define MODULE_SERIAL Serial3

WiFi_my::WiFi_my(unsigned long speed) :IConnector(&MODULE_SERIAL) {
	DEBUG_PRINTLN("Constructor wifi");
	if (is_inited_)
	{
		return;
	}
	is_inited_ = true;
	MODULE_SERIAL.begin(speed);

	connect_to_module();
	if (is_connected_)
	{
		DisplayManager::get_manager()->init_connector(ConnectorEnum::wifi_connector);
	}

	DEBUG_PRINTLN("Constructor wifi end");
}

bool WiFi_my::is_module_connected() const
{
	return is_connected_;
}

bool WiFi_my::is_message_was_read_before_timeout(Timer& timer, const char* to_compare, const uint16_t length)
{
	static const int kDelayMs = 100;

	const bool prev_is_connected = is_connected_;
	is_connected_ = true;

	while (!(is_need_to_read_message() && is_message_equal(to_compare, length)))
	{
		if (timer.isFinished())
		{
			is_connected_ = prev_is_connected;
			return false;
		}
		delay(kDelayMs);
	}
	is_connected_ = prev_is_connected;
	return true;
}

bool WiFi_my::is_message_equal(const char* to_compare, const uint16_t length)
{
	uint8_t buffer[BUFFER_SIZE] = { 0 };
	const uint16_t read_length = read_message(buffer, sizeof(buffer));

	if (length != read_length)
	{
		return false;
	}

	return (memcmp(buffer, to_compare, length) == 0);
}

void WiFi_my::connect_to_module()
{
	const char require_request[] = "I'm ready, Milord!";
	const char require_second_request[] = "Yes, Sir";
	const char responce[] = "Sir";

	Timer timer(Constants::kWifiHandshakeWaitMs);
	timer.start_or_resume();

	if (!is_message_was_read_before_timeout(timer, require_request, strlen(require_request)))
	{
		DEBUG_PRINTLN("Handshake part 1 error");
		return;
	}

	const bool prev_is_connected = is_connected_;
	is_connected_ = true;
	write_answer(reinterpret_cast<const uint8_t*>(responce), strlen(responce));
	is_connected_ = prev_is_connected;

	if (!is_message_was_read_before_timeout(timer, require_second_request, strlen(require_second_request)))
	{
		DEBUG_PRINTLN("Handshake part 3 error");
		return;
	}

	is_connected_ = true;
	DEBUG_PRINTLN("Wi-Fi was connected");
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

	for (int i = 0; i < length && buffer_length < (BUFFER_SIZE - 2); i++, buffer_length++)
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

	buffer_ptr[buffer_length] = stop_symbol_;
	buffer_length++;

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
	uint8_t buffer_ptr[BUFFER_SIZE] = { 0 };
	const int buffer_length = device_->readBytesUntil(stop_symbol_, buffer_ptr, BUFFER_SIZE);

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
