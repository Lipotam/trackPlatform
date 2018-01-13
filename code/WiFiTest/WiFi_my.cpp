#include "WiFi_my.h"

WiFi_my::WiFi_my() :ConnectingDevice(&Serial1) {
	isServerStarted = false;
	for (int i = 0; i <= MAX_CONNECT_ID; i++) {
		connectedIds[i] = NOT_CONNECTED;
	}
	Serial1.begin(WIFI_SPEED);
	Serial.begin(WIFI_SPEED);
	startTcpServer();
}

bool WiFi_my::startTcpServer() {
	String answer;
	Serial1.print(SET_WIFI_MODE_COM);
	answer = readAnswer();
	if (!answer.startsWith(SET_WIFI_MODE_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	Serial.println("WiFi_my mode was set.");

	Serial1.print(ENABLE_MULTIPLE_CONNECTION_COM);
	answer = readAnswer();
	if (!answer.startsWith(ENABLE_MULTIPLE_CONNECTION_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	Serial.println("multiple connection was set.");

	Serial1.print(SETUP_SERVER_COM);
	answer = readAnswer();
	if (!answer.startsWith(SETUP_SERVER_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	Serial.println("server started.");
	Serial.println ("Port: " + PORT);
	isServerStarted = true;
	return true;
}

void WiFi_my::stopConnection(int id) {
	Serial1.print(DELETE_TCP_CONNECTION + String(char(id)) + EOC);
	String answer = readAnswer();
	if (!answer.endsWith(POSITIVE_ANSWER)) {
		Serial.println("Error in deleting the connection.(stopConnection method).");
	}
}

String WiFi_my::readAnswer() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (Serial1.available()) {
			Serial1.readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	Serial.println("Read ans: " + String(buf));
	return String(buf);
}

int WiFi_my::waitClient() {
	String answer = readAnswer();
	String strNumber = answer.substring(0, answer.indexOf(",CONNECT"));
	int num = atoi(strNumber.c_str());
	return num;
}

bool WiFi_my::isActive() {
	return !dataBuffer.isEmpty();
}

String WiFi_my::getMessage() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (Serial1.available()) {
			Serial1.readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	String data = String(buf);
	Serial.println("Read: " + data);
	int infoStartIndex = data.indexOf(":") + 1;
	String info = data.substring(infoStartIndex);
	return info;
}

void WiFi_my::send(String data) {
	if (!data.length()) {
		return;
	}
	String command = SEND_BUFFER_COM + data.length() + EOC;					// may be space needed.(between command and length.)
	Serial1.print(command);
	String answer = readAnswer();
	/*if (!answer.endsWith(">")) {
		Serial.println("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}*/
	Serial1.print(data);
	answer = readAnswer();
	if (!answer.endsWith("SEND OK" + EOC)) {
		Serial.println("Error in answer(method send)");
	}
}

String WiFi_my::read() {
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	if (Serial1.available()) {
		Serial1.readBytes(buf, BUFFER_SIZE);
	}
	else {
		if (dataBuffer.isEmpty()) {
			return String("");
		}
	}
	String bufStr(buf);
	//Serial.println("Buf: " + bufStr);
	String subStr = bufStr.substring(0, bufStr.indexOf("\r\n"));
	while (bufStr.indexOf("\r\n") < bufStr.length()) {
		Serial.println("SubStr: " + subStr);
		/*
		0,CLOSED
		*/
		if (subStr.indexOf(",CONNECT") != -1) {
			String strNumber = subStr.substring(0, subStr.indexOf(",CONNECT"));
			uint32_t num = strNumber.toInt();
			connectedIds[num] = CONNECTED;
			Serial.println("Connected: " + String(num));
		}
		else if (subStr.indexOf(",CLOSED") != -1) {
			String strNumber = subStr.substring(0, subStr.indexOf(",CLOSED"));
			uint32_t num = strNumber.toInt();
			connectedIds[num] = NOT_CONNECTED;
			Serial.println("Disconnected: " + String(num));
		}
		else if (subStr.indexOf("+IPD,") != -1) {
			String data = subStr.substring(subStr.indexOf(":") + 1);
			dataBuffer.push(data);
			Serial.println("Get data: " + data);
		}
		//...
		
		bufStr = bufStr.substring(bufStr.indexOf("\r\n") + 2);
		subStr = bufStr.substring(0, bufStr.indexOf("\r\n"));
	}
	if (!dataBuffer.isEmpty()) {
		return dataBuffer.pop();
	}
	return String("");
}