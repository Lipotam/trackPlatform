#include <iostream>
#include <string>

#include "GamepadManager.h"
#include "ConnectionModes.h"
#include "TrackPlatform_Manager.h"
#include "Logger.h"
#include "ConsolePlatformConnector.h"

int main(int argc, char* argv[])
{
	TrackPlatform_Manager* trackPlatform = nullptr;
	Logger::log("App is running");

	int retCode = 0;

	try
	{
		ConsolePlatformConnector platformConnector;
		trackPlatform = platformConnector.connect();
		if (!trackPlatform)
		{
			return 2;
		}

		std::cout << "Connected" << std::endl;

		GamepadManager manager(trackPlatform);
		manager.run();
		manager.join();
	}
	catch (...)
	{
		std::cout << "Exception was catched" << std::endl;
		Logger::log("Exception was catched");
		retCode = 1;
	}

	if (trackPlatform)
	{
		delete trackPlatform;
	}
	Logger::log("App is closed");
	return retCode;
}

