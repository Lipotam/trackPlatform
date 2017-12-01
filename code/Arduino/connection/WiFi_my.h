#pragma once
#include "../utils/Vector.h"
#include "IConnector.h"

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
const String GET_IP_MAC =						"AT+CIFSR" + EOC;
// port: 333, IP: 192.168.4.1
class WiFi_my : public IConnector
{
private:
	bool is_inited_ = false;
	bool is_server_started_ = false;
	Vector<String> data_buffer_;
	// 1 - there is connection with this ID, 0 - there is no connection with this ID. (id - is num of element)
	uint32_t connected_ids_[MAX_CONNECT_ID + 1];

public:
	
	WiFi_my(unsigned long speed);
	// port is declareted in constants above.
	bool start_tcp_server();
	// if send 5 as id, you will discconect all connections
	void stop_connection(int id);
	String read_answer();
	// retrun number of connection
	int wait_client();
	bool is_need_to_read_message() override;
	// return empty string if there is not data.
	virtual String read_message();
	virtual void write_answer(String data);

	// synchronous methods
	String get_message();
	
};