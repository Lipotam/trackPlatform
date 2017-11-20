#include "WiFi_my.h"

WiFi_my::WiFi_my() :ConnectingDevice(&Serial1) {
	isServerStarted = false;
	Serial1.begin(WIFI_SPEED);
	Serial.begin(WIFI_SPEED);
	//read();												// read info which module send after it started
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

void WiFi_my::stopConnection() {
	Serial1.print(DELETE_TCP_CONNECTION);
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
	Serial.println("Read: " + String(buf));
	return String(buf);
}

bool WiFi_my::isActive() {
	return isServerStarted;
}

String WiFi_my::read() {
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
	String command = SEND_BUFFER_COM + data.length() + EOC;					// may be space needed.(between command and length.
	Serial1.print(command);
	String answer = readAnswer();
	if (!answer.endsWith(">" + EOC)) {
		Serial.println("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}
	Serial1.print(data);
}