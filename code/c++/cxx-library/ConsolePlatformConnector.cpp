#include "ConsolePlatformConnector.h"

TrackPlatform_Manager* ConsolePlatformConnector::connect()
{
	int answer = 0;

	std::cout << "Connect by:" << std::endl;
	std::cout << "\t1) USB" << std::endl;
	std::cout << "\t2) Bluetooth" << std::endl;
	std::cout << "\t3) WiFi" << std::endl;
	std::cin >> answer;

	switch (answer)
	{
	case 1:
	case 2:
		return connectBySerial();
	case 3:
		return connectByTcpIp();
	default: 
		std::cout << "No connector at number " << answer << std::endl;
		return nullptr;
	}
}

TrackPlatform_Manager* ConsolePlatformConnector::connectBySerial()
{
	std::string rtx = "COM13";
	uint32_t baudrate = 9600U;

	std::cout << "port" << std::endl;
	std::cin >> rtx;
	std::cout << "baudrate" << std::endl;
	std::cin >> baudrate;

	std::cout << "rx = " << rtx << " tx = " << rtx << " baudrate = " << baudrate << std::endl;

	CommunicationInfoStruct info;

	info.SerialInfo.rxPort = rtx;
	info.SerialInfo.txPort = rtx;
	info.SerialInfo.baudrate = baudrate;
	return new TrackPlatform_Manager(bluetooth, info);
}

TrackPlatform_Manager* ConsolePlatformConnector::connectByTcpIp()
{
	std::string ip = "192.168.4.1";
	uint16_t port = 333;

	std::cout << "server ip" << std::endl;
	std::cin >> ip;
	std::cout << "port" << std::endl;
	std::cin >> port;

	std::cout << "ip = " << ip << " port = " << port << std::endl;

	CommunicationInfoStruct info;

	info.TCPIPInfo.ip = ip;
	info.TCPIPInfo.port = port;
	return new TrackPlatform_Manager(WiFi, info);
}
