#include <string.h>

#include "../connection/USB.h"
#include "../connection/Bluetooth.h"
#include "../connection/WiFi.h"
#include "../config/Constants.h"
#include "../connection/DebugSerial.h"
#include "../management/MainManager.h"

#include "ConnectionManager.h"

ConnectionManager* ConnectionManager::manager = nullptr;

ConnectionManager::ConnectionManager()
{
	connectors = new IConnector*[connectors_num];
	connectors[0] = new USB(Constants::usb_serial_speed);
	connectors[1] = new Bluetooth(Constants::bluetooth_serial_speed);
	//connectors[2] = new WiFi(Constants::wifi_serial_speed);
}

ConnectionManager::ConnectionManager(ConnectionManager&)
{
	timer.startOrResume();
}

ConnectionManager* ConnectionManager::get_manager()
{
	if (!manager)
	{
		manager = new ConnectionManager();
	}
	return manager;
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
		connection_status = not_connected;
		DEBUG_PRINTLN("Disconnect by timeout");
		return empty;
	}

	if (!current_connector)
	{
		DEBUG_PRINTLN("Bad connector when trying to read");
		return empty;
	}

	if (current_connector->is_need_to_read_message())
	{
		String read = current_connector->read_message();
		if (is_message_is_command(read))
		{
			write_answer(Constants::good_answer);
			timer.reset();
			return get_data_from_wrapper(read);
		}

		write_answer(Constants::bad_answer);
		DEBUG_PRINT("Received message is not a command ");
		DEBUG_PRINTLNHEX(read);
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

bool ConnectionManager::is_message_is_command(String message)
{
	if (message.length() < static_cast<unsigned int>(length_length + crc_length))
	{
		DEBUG_PRINTF("Message size %d is too little\n", message.length());
		return false;
	}

	byte len = 0;
	memcpy(&len, message.c_str(), length_length);

	if (message.length() != static_cast<unsigned int>(len + length_length + crc_length))
	{
		DEBUG_PRINTF("Message size %d is not equal first byte %d\n", message.length(), (len + length_length + crc_length));
		return false;
	}

	const uint16_t crc = crc_calculator.modbus(reinterpret_cast<const byte*>(message.c_str()), message.length());

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
	answer = convert_pointer_to_string(&len, length_length) + answer;

	const uint16_t crc = crc_calculator.modbus(reinterpret_cast<const uint8_t*>(answer.c_str()), answer.length());
	answer += convert_pointer_to_string(&crc, crc_length);

	if (current_connector)
	{
		current_connector->write_answer(answer);
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
	connection_status = connected;
}

void ConnectionManager::reset_current_connection()
{
	connection_status = not_connected;
}

void ConnectionManager::reset_timer()
{
	timer.reset();
}

void ConnectionManager::wait_for_connection()
{
	DEBUG_PRINTLN("Arduino tries to found a manager");

	connection_status = try_connect;

	int connector_index = connectors_num - 1;
	while (!is_connected()) {
		connector_index = (connector_index + 1) % connectors_num;
		current_connector = connectors[connector_index];
		timer.reset();

		MainManager::get_manager()->run();
	}

	DEBUG_PRINTF("Arduino found a manager with index %d\n", connector_index);
}

String ConnectionManager::get_data_from_wrapper(String message)
{
	//remove length
	message.remove(0, length_length);

	//remove crc
	message.remove(message.length() - crc_length, crc_length);

	return message;
}

//bool ConnectionManager::wait_for_command_on_device(Timer* timer)
//{
//	//compatibility with API v1 & v2
//	if (connectedAPIversion >= APIWithAutoDiconnect)
//	{
//		while (!current_connector->is_need_to_read_message() && timer->getState() != timerState_finished)
//		{
//			delay(1);
//		}
//
//		if (timer->getState() == timerState_finished)
//		{
//			return false;
//		}
//	}
//	else
//	{
//		while (!current_connector->is_need_to_read_message())
//		{
//			delay(1);
//		}
//	}
//
//	return true;
//}
//
//String ConnectionManager::read_command()
//{
//	if (!isConnected)
//	{
//		return "";
//	}
//
//	String command;
//	Timer timer(Constants::wait_command_time_in_ms);
//	timer.startOrResume();
//	do
//	{
//		if (!wait_for_command_on_device(&timer))
//		{
//			isConnected = false;
//			wait_for_connection();
//			timer.reset();
//			continue;
//		}
//
//		command = current_connector->read_message();
//
//		//API v1 & v2 compatibility
//		if (connectedAPIversion >= APIWithAnswer)
//		{
//			current_connector->write_answer("OK");
//		}
//
//		//debug
//		DEBUG_PRINT("Command: ");
//		DEBUG_PRINTLNHEX(command);
//
//		if (command == disconnectCommand)
//		{
//			isConnected = false;
//			wait_for_connection();
//			timer.reset();
//			continue;
//		}
//
//		if (connectedAPIversion >= APIWithAutoDiconnect && command == refreshCommand)
//		{
//			timer.reset();
//			continue;
//		}
//
//		break;
//	} while (true);
//	return command;
//}
