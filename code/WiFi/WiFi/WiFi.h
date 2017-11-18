#pragma once
#include "ConnectingDevice.h"

const int WIFI_SPEED =							115200;
const int BUFFER_SIZE =							255;

// COM = command, EOC = end of command.
HardwareSerial* pDebugSerial =					&Serial;
HardwareSerial* pUsesSerial =					&Serial1;
const String PORT =								"333";
const String LINK_ID =							"0";
const String EOC =								"\r\n";							// end of command
const String POSITIVE_ANSWER =					"OK" + EOC;
const String NEGATIVE_ANWSER =					"ERROR" + EOC;
const String SET_WIFI_MODE_COM =				"AT+CWMODE=3" + EOC;
const String ENABLE_MULTIPLE_CONNECTION_COM =	"AT+CIPMUX=1" + EOC;
const String SETUP_SERVER_COM =					"AT+CIPSERVER=1," + PORT;	
const String SEND_BUFFER_COM =					"AT+CIPSENDBUF" + LINK_ID;

class WiFi : public ConnectingDevice
{
private:
	bool isServerStarted;

public:
	WiFi();
	// port is declareted in constants above.
	bool startTcpServer();
	String readAnswer();
	virtual bool isActive();
	virtual String read();
	virtual void send(String data);
};