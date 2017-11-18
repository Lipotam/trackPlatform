#include "WiFi.h"

WiFi::WiFi() :ConnectingDevice(pUsesSerial) {
	isServerStarted = false;
	pUsesSerial->begin(WIFI_SPEED);
	pDebugSerial->begin(WIFI_SPEED);
	read();												// read info which module send after it started
	startTcpServer();
}

bool WiFi::startTcpServer() {
	String answer;
	pUsesSerial->print(SET_WIFI_MODE_COM);
	answer = readAnswer();
	if (!answer.startsWith(SET_WIFI_MODE_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	pDebugSerial->println("wifi mode was set.");

	pUsesSerial->print(ENABLE_MULTIPLE_CONNECTION_COM);
	answer = readAnswer();
	if (!answer.startsWith(ENABLE_MULTIPLE_CONNECTION_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	pDebugSerial->println("multiple connection was set.");

	pUsesSerial->print(SETUP_SERVER_COM);
	answer = readAnswer();
	if (!answer.startsWith(SETUP_SERVER_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		isServerStarted = false;
		return false;
	}
	pDebugSerial->println("server started.");
	pDebugSerial->println ("Port: " + PORT);
	isServerStarted = true;
	return true;
}

String WiFi::readAnswer() {
	char buf[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (pUsesSerial->available()) {
			pUsesSerial->readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	pDebugSerial->println("Read: " + String(buf));
	return String(buf);
}

bool WiFi::isActive() {
	return isServerStarted;
}

String WiFi::read() {
	char buf[BUFFER_SIZE];
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (pUsesSerial->available()) {
			pUsesSerial->readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	String data = String(buf);
	pDebugSerial->println("Read: " + data);
	int infoStartIndex = data.indexOf(": ") + 2;
	String info = data.substring(infoStartIndex);
	return info;
}

void WiFi::send(String data) {
	String command = SEND_BUFFER_COM + data.length();					// may be space needed.(between command and length.
	pUsesSerial->print(command);
	String answer = readAnswer();
	if (!answer.endsWith(">" + EOC)) {
		pDebugSerial->println("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}
	pUsesSerial->print(data);
}