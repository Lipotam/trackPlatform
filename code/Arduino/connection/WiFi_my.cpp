#include "WiFi_my.h"
#include "DebugSerial.h"

WiFi_my::WiFi_my() :IConnector(&Serial2) {
	//Добавить вывод IP
	DEBUG_PRINTLN("Constructor wifi");
	if (isInited)
	{
		return;
	}
	isInited = true;
	Serial2.begin(WIFI_SPEED);
	isServerStarted = false;
	DEBUG_PRINTLN("Constructor wifi2");
	for (uint32_t i = 0; i <= MAX_CONNECT_ID; i++) {
		connectedIds[i] = NOT_CONNECTED;
	}
	Serial2.begin(WIFI_SPEED);
	startTcpServer();
	DEBUG_PRINTLN("Constructor wifi3");
}

bool WiFi_my::startTcpServer() {
	String answer;
	Serial2.print(SET_WIFI_MODE_COM);
	answer = readAnswer();
	if (!answer.startsWith(SET_WIFI_MODE_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("WiFi_my mode was set.");

	Serial2.print(ENABLE_MULTIPLE_CONNECTION_COM);
	answer = readAnswer();
	if (!answer.startsWith(ENABLE_MULTIPLE_CONNECTION_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("multiple connection was set.");

	Serial2.print(SETUP_SERVER_COM);
	answer = readAnswer();
	if (!answer.startsWith(SETUP_SERVER_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	DEBUG_PRINTLN("server started.");
	DEBUG_PRINTLN("Port: " + PORT);
	isServerStarted = true;
	return true;
}

void WiFi_my::stopConnection(int id) {
	Serial2.print(DELETE_TCP_CONNECTION + String(char(id)) + EOC);
	String answer = readAnswer();
	if (!answer.endsWith(POSITIVE_ANSWER)) {
		DEBUG_PRINTLN("Error in deleting the connection.(stopConnection method).");
	}
}

String WiFi_my::readAnswer() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (Serial2.available()) {
			Serial2.readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	DEBUG_PRINTLN("Read ans: " + String(buf));
	return String(buf);
}

int WiFi_my::waitClient() {
	String answer = readAnswer();
	String strNumber = answer.substring(0, answer.indexOf(",CONNECT"));
	int num = atoi(strNumber.c_str());
	return num;
}

bool WiFi_my::is_need_to_read_message() {
	//DEBUG_PRINTLN("IMPORTANT: " + String((int)'\|'));
	DEBUG_PRINTLN(String(__LINE__));
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	if (Serial2.available()) {
		Serial2.readBytes(buf, BUFFER_SIZE);
	}
	else {
		return !dataBuffer.isEmpty();
	}
	String bufStr(buf);
	//DEBUG_PRINTLN("Buf: " + bufStr);
	String subStr = bufStr.substring(0, bufStr.indexOf("\r\n"));
	while (bufStr.indexOf("\r\n") != -1) {
		//DEBUG_PRINTLN("SubStr: " + subStr);
		if (subStr.indexOf(",CONNECT") != -1) {
			String strNumber = subStr.substring(0, subStr.indexOf(",CONNECT"));
			uint32_t num = strNumber.toInt();
			connectedIds[num] = CONNECTED;
			DEBUG_PRINTLN("Connected: " + String(num));
		}
		else if (subStr.indexOf(",CLOSED") != -1) {
			String strNumber = subStr.substring(0, subStr.indexOf(",CLOSED"));
			uint32_t num = strNumber.toInt();
			connectedIds[num] = NOT_CONNECTED;
			DEBUG_PRINTLN("Disconnected: " + String(num));
		}
		else if (subStr.indexOf("+IPD,") != -1) {
			String data = subStr.substring(subStr.indexOf(":") + 1);
			dataBuffer.push(data);
			DEBUG_PRINT("Get data: ");
			DEBUG_PRINTLNHEX(data);
		}
		//...

		bufStr = bufStr.substring(bufStr.indexOf("\r\n") + 2);
		subStr = bufStr.substring(0, bufStr.indexOf("\r\n"));
	}
	DEBUG_PRINTLN(String(__LINE__));
	return !dataBuffer.isEmpty();
}

String WiFi_my::getMessage() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (Serial2.available()) {
			Serial2.readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	String data = String(buf);
	DEBUG_PRINTLN("Read: " + data);
	int infoStartIndex = data.indexOf(":") + 1;
	String info = data.substring(infoStartIndex);
	return info;
}

void WiFi_my::write_answer(String data) {
	if (!data.length()) {
		return;
	}
	String command = SEND_BUFFER_COM + data.length() + EOC;					// may be space needed.(between command and length.)
	Serial2.print(command);
	String answer = readAnswer();
	/*if (!answer.endsWith(">")) {
		DEBUG_PRINTLN("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}*/
	Serial2.print(data);
	answer = readAnswer();
	if (!answer.endsWith("SEND OK" + EOC)) {
		DEBUG_PRINTLN("Error in answer(method send)");
	}
}

String WiFi_my::read_message() {

	if (!dataBuffer.isEmpty()) {
		String data = dataBuffer.pop();
		data = data.substring(0, data.indexOf("|"));
		DEBUG_PRINT("FROM VECTOR: ");
		DEBUG_PRINTLNHEX(data);
		return data;
	}
	return String();
}