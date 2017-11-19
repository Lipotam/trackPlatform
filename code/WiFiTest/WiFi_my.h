#pragma once 
#include "ConnectingDevice.h"
#include <USBAPI.h>

const uint32_t WIFI_SPEED =						115200;
const uint32_t BUFFER_SIZE =					255;

// COM = command, EOC = end of command.
//Serial_* pDebugSerial =							&Serial;
//HardwareSerial* pUsesSerial =					&Serial1;
const String PORT =								"333";
const String LINK_ID =							"0";
const String EOC =								"\r\n";							// end of command
const String POSITIVE_ANSWER =					"OK" + EOC;
const String NEGATIVE_ANWSER =					"ERROR" + EOC;
const String SET_WIFI_MODE_COM =				"AT+CWMODE=3" + EOC;
const String ENABLE_MULTIPLE_CONNECTION_COM =	"AT+CIPMUX=1" + EOC;
const String SETUP_SERVER_COM =					"AT+CIPSERVER=1," + PORT + EOC;
const String SEND_BUFFER_COM =					"AT+CIPSENDBUF=" + LINK_ID + ",";
const String DELETE_TCP_CONNECTION =			"AT+CIPCLOSE=" + LINK_ID + EOC;

class WiFi_my : public ConnectingDevice
{
private:
	bool isServerStarted;

public:
	
	WiFi_my();
	// port is declareted in constants above.
	bool startTcpServer();
	void stopConnection();
	String readAnswer();
	virtual bool isActive();
	virtual String read();
	virtual void send(String data);
	
};