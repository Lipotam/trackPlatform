#include "../connection/USB.h"
#include "../connection/Bluetooth.h"
#include "../connection/WiFi.h"
#include "../config/Constants.h"
#include "../connection/DebugSerial.h"

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
	//TODO
	return "";
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
	//TODO
	return false;
}

void ConnectionManager::write_answer(String answer)
{
	const byte len = answer.length();
	answer = convert_pointer_to_string(&len, sizeof(len)) + answer;

	const uint16_t crc = crc_calculator.modbus(reinterpret_cast<const uint8_t*>(answer.c_str()), answer.length());
	answer += convert_pointer_to_string(&crc, sizeof(crc));

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

	//TODO

	//while (!isConnected) {
	//	//waiting some info
	//	while (!bluetooth->is_need_to_read_message() && !usb->is_need_to_read_message() && !wifi->is_need_to_read_message())
	//	{
	//		delay(1);
	//	}

	//	DEBUG_PRINTLN("Info was found");

	//	//reading info
	//	if (bluetooth->is_need_to_read_message()) {
	//		current_connector = bluetooth;
	//		DEBUG_PRINTLN("Bluetooth sends something");
	//	}
	//	else if (wifi->is_need_to_read_message()) {
	//		current_connector = wifi;
	//		DEBUG_PRINTLN("Wifi sends something");
	//	}
	//	else if (usb->is_need_to_read_message()) {
	//		current_connector = usb;
	//		DEBUG_PRINTLN("USB sends something");
	//	}

	//	String readInfo = current_connector->read_message();

	//	//check first part of command (if that command is connection command)
	//	if (readInfo.length() < sizeof (connectCommand) || (readInfo.substring(0, sizeof(connectCommand) - 1) != connectCommand))
	//	{
	//		DEBUG_PRINT("Bad info: ");
	//		DEBUG_PRINTLNHEX(readInfo);
	//		continue;
	//	}

	//	readInfo = readInfo.substring(sizeof(connectCommand) - 1);

	//	//check API version length
	//	if (readInfo.length() != 1)
	//	{
	//		DEBUG_PRINTF("Bad API version. Version was very long: %d symbols\n", readInfo.length());
	//		continue;
	//	}

	//	//check API version
	//	connectedAPIversion = static_cast<StartCommands>(readInfo[0]);
	//	if (connectedAPIversion > highestAPI || connectedAPIversion < lowestAPI)
	//	{
	//		DEBUG_PRINTF("Bad API version. Was %d, required in [%d, %d] interval\n", connectedAPIversion, lowestAPI, highestAPI);
	//		continue;
	//	}		
	//	DEBUG_PRINTF("Connected API version: %d\n", connectedAPIversion);
	//	isConnected = true;
	//}

	////API v1 & v2 compatibility
	//if (connectedAPIversion >= APIWithAnswer)
	//{
	//	current_connector->write_answer("OK");
	//}
	DEBUG_PRINTLN("Arduino found a manager");
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
