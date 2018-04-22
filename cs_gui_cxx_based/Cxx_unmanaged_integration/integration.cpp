#include "integration.h"
#include "SensorViewCSharp.h"

namespace
{
	TrackPlatform_Manager* trackPlatformManager = nullptr;
	SensorViewCSharp viewer;
}

GamepadManager* connect(char* com_address, const unsigned long speed)
{
	try
	{
		CommunicationInfoStruct info;

		info.SerialInfo.rxPort = std::string(com_address);
		info.SerialInfo.txPort = std::string(com_address);
		info.SerialInfo.baudrate = speed;

		trackPlatformManager = new TrackPlatform_Manager(USB, info);
		if (!trackPlatformManager)
		{
			return nullptr;
		}

		GamepadManager* manager = new GamepadManager(trackPlatformManager, &viewer);
		manager->run();

		return manager;
	}
	catch (...)
	{
		return nullptr;
	}
}

void disconnect(GamepadManager* manager)
{
	try
	{
		manager->join();
	}
	catch (...)
	{
		//all is good
	}

	if (trackPlatformManager)
	{
		delete trackPlatformManager;
		trackPlatformManager = nullptr;
	}
}

void set_sensor_callbacks(sensor_callback distanceSensorCallback, sensor_callback lineSensorCallback)
{
	viewer.setLineCallback(lineSensorCallback);
	viewer.setDistanceCallback(distanceSensorCallback);
}
