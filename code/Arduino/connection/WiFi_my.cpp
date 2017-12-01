#include "WiFi_my.h"
#include "DebugSerial.h"

WiFi_my::WiFi_my(unsigned long speed) :IConnector(&Serial2) {
	//Добавить вывод IP
	DEBUG_PRINTLN("Constructor wifi");
	if (isInited)
	{
		return;
	}
	isInited = true;
	Serial2.begin(speed);

	isServerStarted = false;
	DEBUG_PRINTLN("Constructor wifi2");
	for (uint32_t i = 0; i <= MAX_CONNECT_ID; i++) {
		connectedIds[i] = NOT_CONNECTED;
	}
	start_tcp_server();
	DEBUG_PRINTLN("Constructor wifi3");
}

bool WiFi_my::start_tcp_server() {
	device->print(SET_WIFI_MODE_COM);
	read_answer();
	String answer = String(reinterpret_cast<char*>(buffer_));
	if (!answer.startsWith(SET_WIFI_MODE_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("WiFi_my mode was set.");

	device->print(ENABLE_MULTIPLE_CONNECTION_COM);
	read_answer();
	answer = String(reinterpret_cast<char*>(buffer_));
	if (!answer.startsWith(ENABLE_MULTIPLE_CONNECTION_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("multiple connection was set.");

	device->print(SETUP_SERVER_COM);
	read_answer();
	answer = String(reinterpret_cast<char*>(buffer_));
	if (!answer.startsWith(SETUP_SERVER_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("server started.");
	DEBUG_PRINTLN("Port: " + PORT);
	device->print(GET_IP_MAC);
	read_answer();
	answer = String(reinterpret_cast<char*>(buffer_));
	String ip = answer.substring(answer.indexOf("+CIFSR:APIP,\"") + String("+CIFSR:APIP,\"").length(),
		answer.indexOf("+CIFSR:APMAC,") - 3);
	DEBUG_PRINTLN("IP: " + ip);
	isServerStarted = true;
	return true;
}

void WiFi_my::stop_connection(int id) {
	device->print(DELETE_TCP_CONNECTION + String(char(id)) + EOC);
	read_answer();
	String answer = String(reinterpret_cast<char*>(buffer_));
	if (!answer.endsWith(POSITIVE_ANSWER)) {
		DEBUG_PRINTLN("Error in deleting the connection.(stopConnection method).");
	}
}

void WiFi_my::read_answer() {
	memset(buffer_, 0, sizeof(buffer_));

	while (!device->available())
	{
	}

	buffer_length_ = device->readBytes(buffer_, sizeof(buffer_));

	DEBUG_PRINTLN("Read ans: " + String(reinterpret_cast<char*>(buffer_)));
}

int WiFi_my::wait_client() {
	read_answer();
	String answer(reinterpret_cast<char*>(buffer_));
	String str_number = answer.substring(0, answer.indexOf(",CONNECT"));
	return atoi(str_number.c_str());
}

bool WiFi_my::is_need_to_read_message() {
	//DEBUG_PRINTLN("IMPORTANT: " + String((int)'\|'));
	//DEBUG_PRINTLN(String(__LINE__));
	
	read_answer();

	String buf_str = String(reinterpret_cast<char*>(buffer_));
	if (buf_str.startsWith("\r\n")) {
		buf_str = buf_str.substring(2);
	}
	//DEBUG_PRINTLN("Buf: ");
	//DEBUG_PRINTLNHEX(bufStr);
	String sub_str = buf_str.substring(0, buf_str.indexOf("\r\n"));
	//uint32_t starOfNewSubstr = bufStr.indexOf("\r\n") + 2;
	while (buf_str.indexOf("\r\n") != -1) {
		//DEBUG_PRINT("SubStr: ");
		//DEBUG_PRINTLNHEX(subStr);
		if (sub_str.indexOf(",CONNECT") != -1) {
			String str_number = sub_str.substring(0, sub_str.indexOf(",CONNECT"));
			uint32_t num = str_number.toInt();
			connectedIds[num] = CONNECTED;
			DEBUG_PRINTLN("Connected: " + String(num));
		}
		else if (sub_str.indexOf(",CLOSED") != -1) {
			String str_number = sub_str.substring(0, sub_str.indexOf(",CLOSED"));
			uint32_t num = str_number.toInt();
			connectedIds[num] = NOT_CONNECTED;
			DEBUG_PRINTLN("Disconnected: " + String(num));
		}
		else if (sub_str.indexOf("+IPD,") != -1) {
			String data = sub_str.substring(sub_str.indexOf(":") + 1);
			if (data.length()) {
				//dataBuffer.push(data);
				memcpy(buffer_, data.c_str(), data.length());
				buffer_length_ = data.length();
				DEBUG_PRINT("Get data: ");
				DEBUG_PRINTLNHEX(buffer_, buffer_length_);
			}
		}
		//...

		buf_str = buf_str.substring(buf_str.indexOf("\r\n") + 2);
		sub_str = buf_str.substring(0, buf_str.indexOf("\r\n"));
	}
	//DEBUG_PRINTLN(String(__LINE__));
	return !dataBuffer.isEmpty();
}

String WiFi_my::get_message() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (device->available()) {
			device->readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	String data = String(buf);
	DEBUG_PRINTLN("Read: " + data);
	int info_start_index = data.indexOf(":") + 1;
	String info = data.substring(info_start_index);
	return info;
}

void WiFi_my::write_answer(String data) {
	if (!data.length()) {
		return;
	}
	String command = SEND_BUFFER_COM + data.length() + EOC;					// may be space needed.(between command and length.)
	device->print(command);
	read_answer();
	String answer = String(reinterpret_cast<char*>(buffer_));
	/*if (!answer.endsWith(">")) {
		DEBUG_PRINTLN("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}*/
	device->print(data);
	read_answer();
	answer = String(reinterpret_cast<char*>(buffer_));
	if (!answer.endsWith("SEND OK" + EOC)) {
		DEBUG_PRINTLN("Error in answer(method send)");
	}
}

int WiFi_my::read_message(uint8_t* pointer, int max_length) {

	memcpy(pointer, buffer_, buffer_length_);
	return buffer_length_;
}