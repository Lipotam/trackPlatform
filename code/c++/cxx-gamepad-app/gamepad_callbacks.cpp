#include "GamepadManager.h"
#include "gamepad_callbacks.h"

void onButtonDown(Gamepad_device* device, unsigned buttonID, double timestamp, void* context)
{
	GamepadManager* manager = static_cast<GamepadManager*>(context);
	switch (manager->getConfig().button(buttonID))
	{
	case GamepadCommands::exit: {
		manager->stop();
		break;
	}
	case GamepadCommands::lineSensorRefresh: {
		auto values = manager->getTrackPlatformManager()->sensorLineGetAllValues();
		//TODO: show on screen
		break;
	}
	case GamepadCommands::distanceSensorRefresh: {
		auto values = manager->getTrackPlatformManager()->sensorDistanceGetAllValues();
		//TODO: show on screen
		break;
	}
	default: break;
	}
}

void onButtonUp(Gamepad_device* device, unsigned buttonID, double timestamp, void* context)
{
}

void onAxisMoved(Gamepad_device* device, unsigned axisID, float value, float lastValue, double timestamp, void* context)
{
	GamepadManager* manager = static_cast<GamepadManager*>(context);
	switch (manager->getConfig().stick(axisID))
	{
		//TODO: process sticks
	default: break;
	}
}
