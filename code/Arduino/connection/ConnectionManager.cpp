#include "../connection/USB.h"
#include "../connection/Bluetooth.h"
#include "../connection/WiFi_my.h"
#include "../config/Constants.h"
#include "../connection/DebugSerial.h"
#include "../management/MainManager.h"
#include "ConnectorEnum.h"
#include "../peripheral/display/DisplayManager.h"

#include "ConnectionManager.h"

ConnectionManager* ConnectionManager::manager_ = nullptr;

ConnectionManager::ConnectionManager(): current_connector_index(0)
{
	connectors = new IConnector*[connectors_num];
	DisplayManager::get_manager()->repaint();
	connectors[ConnectorEnum::usb_connector] = new USB(Constants::kUsbSerialSpeed);
	DisplayManager::get_manager()->repaint();
	connectors[ConnectorEnum::bluetooth_connector] = new Bluetooth(Constants::kBluetoothSerialSpeed);
	DisplayManager::get_manager()->repaint();
	connectors[ConnectorEnum::wifi_connector] = new WiFi_my(Constants::kWifiSerialSpeed);
	DisplayManager::get_manager()->repaint();

	timer.start_or_resume();
}

ConnectionManager* ConnectionManager::get_manager()
{
	if (!manager_)
	{
		manager_ = new ConnectionManager();
	}
	return manager_;
}

String ConnectionManager::read_command()
{
	if (connection_status == not_connected)
	{
		wait_for_connection();
	}

	String empty;

	if (timer.isFinished())
	{
		reset_current_connection();
		DEBUG_PRINTLN("Disconnect by timeout");
		MainManager::get_manager()->stop_all();
		return empty;
	}

	if (!current_connector)
	{
		DEBUG_PRINTLN("Bad connector when trying to read");
		return empty;
	}

	if (current_connector->is_need_to_read_message())
	{
		uint8_t buff[BUFFER_SIZE] = { 0 };
		const int length = current_connector->read_message(buff, BUFFER_SIZE);
		if (is_message_is_command(buff, length))
		{
			write_answer(Constants::kGoodAnswer);
			timer.reset();
			return get_data_from_wrapper(buff, length);
		}

		write_answer(Constants::kBadAnswer);
		DEBUG_PRINT("Received message is not a command ");
		DEBUG_PRINTLNHEX(buff, length);
	}

	return empty;
}

ConnectionManager::~ConnectionManager()
{
	if (connectors) {
		for (int i = 0; i < connectors_num; ++i) {
			if (connectors[i]) {
				delete connectors[i];
			}
		}

		delete[] connectors;
	}
}

String ConnectionManager::convert_pointer_to_string(const void* ptr, int size)
{
	const char* char_ptr = reinterpret_cast<const char*>(ptr);
	String res;
	for (int i = 0; i < size; ++i)
	{
		res += char_ptr[i];
	}
	return res;
}

bool ConnectionManager::is_message_is_command(uint8_t* buffer, int length)
{
	if (length < (length_length + crc_length))
	{
		DEBUG_PRINTF("Message size %d is too little\n", length);
		return false;
	}

	byte len = 0;
	memcpy(&len, buffer, length_length);

	if (length != (len + length_length + crc_length))
	{
		DEBUG_PRINTF("Message size %d is not equal first byte %d\n", length, (len + length_length + crc_length));
		return false;
	}

	const uint16_t crc = crc_calculator.modbus(buffer, length);

	if (crc != 0)
	{
		DEBUG_PRINTF("Bad crc. Calculated %04X\n", crc);
		return false;
	}

	return true;
}

void ConnectionManager::write_answer(String answer)
{
	const byte len = answer.length();

	uint8_t buffer[BUFFER_SIZE] = {0};
	uint8_t buffer_length = 0;
	memcpy(buffer + buffer_length, &len, length_length);
	buffer_length += length_length;
	memcpy(buffer + buffer_length, answer.c_str(), len);
	buffer_length += len;

	const uint16_t crc = crc_calculator.modbus(buffer, buffer_length);
	memcpy(buffer + buffer_length, &crc, crc_length);
	buffer_length += crc_length;

	if (current_connector)
	{
		current_connector->write_answer(buffer, buffer_length);
	}
	else
	{
		DEBUG_PRINTLN("Current connector no set to write answer");
	}
}

bool ConnectionManager::is_connected() const
{
	return connection_status == connected;
}

void ConnectionManager::set_current_connection()
{
	DisplayManager::get_manager()->set_connector(static_cast<ConnectorEnum>(current_connector_index));
	connection_status = connected;
	DEBUG_PRINTLN("Connected successful");
}

void ConnectionManager::reset_current_connection()
{
	DisplayManager::get_manager()->reset_all_connectors();
	connection_status = not_connected;
	DEBUG_PRINTLN("Disconnected successful");
}

void ConnectionManager::reset_timer()
{
	timer.reset();
	DEBUG_PRINTLN("Timer resetting successful");
}

void ConnectionManager::wait_for_connection()
{
	DEBUG_PRINTLN("Arduino tries to found a manager");

	connection_status = try_connect;

	current_connector_index = connectors_num - 1;
	while (!is_connected()) {
		current_connector_index = (current_connector_index + 1) % connectors_num;
		current_connector = connectors[current_connector_index];

		timer.start_or_resume();
		timer.reset();

		MainManager::get_manager()->run();
	}

	DEBUG_PRINTF("Arduino found a manager with index %d\n", current_connector_index);
}

String ConnectionManager::get_data_from_wrapper(uint8_t* buffer, int length)
{
	String answer;

	for (int i = 1; i < (length - crc_length); ++i)
	{
		answer += static_cast<char>(buffer[i]);
	}

	return answer;
}
