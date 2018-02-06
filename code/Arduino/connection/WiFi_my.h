#pragma once
#include "IConnector.h"

// port: 333, IP: 192.168.4.1
class WiFi_my : public IConnector
{
private:
	bool is_inited_ = false;
	bool is_connected_ = false;

	void connect_to_module();
	bool is_message_was_read_before_timeout(Timer& timer, const String& to_compare);
	bool is_message_equal(const String& to_compare);

public:
	WiFi_my(unsigned long speed);

	bool is_module_connected() const;
	bool is_need_to_read_message() override;
	// return empty string if there is not data.
	int read_message(uint8_t* pointer, int max_length) override;
	void write_answer(const uint8_t* answer_ptr, int length) override;
};