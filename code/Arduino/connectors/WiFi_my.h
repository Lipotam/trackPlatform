#pragma once 
#include "ConnectingDevice.h"
#include "../utils/Vector.h"

const uint32_t WIFI_SPEED =						115200;
const uint32_t BUFFER_SIZE =					500;
const uint32_t MAX_CONNECT_ID =					4;
const uint32_t CONNECTED =						1;
const uint32_t NOT_CONNECTED =					0;

// COM = command, EOC = end of command.
const String PORT =								"333";
const String LINK_ID =							"0";
const String EOC =								"\r\n";							// end of command
const String POSITIVE_ANSWER =					"OK" + EOC;
const String NEGATIVE_ANWSER =					"ERROR" + EOC;
const String SET_WIFI_MODE_COM =				"AT+CWMODE=3" + EOC;
const String ENABLE_MULTIPLE_CONNECTION_COM =	"AT+CIPMUX=1" + EOC;
const String SETUP_SERVER_COM =					"AT+CIPSERVER=1," + PORT + EOC;
const String SEND_BUFFER_COM =					"AT+CIPSENDBUF=" + LINK_ID + ",";
const String DELETE_TCP_CONNECTION =			"AT+CIPCLOSE=";

// port: 333, IP: 192.168.4.1
class WiFi_my : public ConnectingDevice
{
private:
	bool isInited = false;
	bool isServerStarted = false;
	Vector<String> dataBuffer;
	// 1 - there is connection with this ID, 0 - there is no connection with this ID. (id - is num of element)
	uint32_t connectedIds[MAX_CONNECT_ID + 1];

public:
	
	WiFi_my();
	// port is declareted in constants above.
	bool startTcpServer();
	// if send 5 as id, you will discconect all connections
	void stopConnection(int id);
	String readAnswer();
	// retrun number of connection
	int waitClient();
	virtual bool isActive();
	// return empty string if there is not data.
	virtual String read();
	virtual void send(String data);

	// synchronous methods
	String getMessage();
	
};