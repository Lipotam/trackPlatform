#include <iostream>
#include <string>

#include "GamepadManager.h"
#include "ConnectionModes.h"
#include "TrackPlatform_Manager.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	std::string rtx = "COM13";
	uint32_t baudrate = 9600U;

	std::cout << "rx = tx = " << rtx << "; baudrate = " << baudrate << std::endl;

	Logger::log("Add is running");

	try
	{
		CommunicationInfoStruct info;
		info.SerialInfo.rxPort = rtx;
		info.SerialInfo.txPort = rtx;
		info.SerialInfo.baudrate = baudrate;
		TrackPlatform_Manager trackPlatform(bluetooth, info);
		GamepadManager manager(&trackPlatform);
		manager.run();
		manager.join();
	}
	catch(...)
	{
		std::cout << "Exception was catched" << std::endl;
		Logger::log("Exception was catched");
		return 1;
	}

	Logger::log("App is closed");
	return 0;
}

