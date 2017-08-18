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
	case GamepadCommands::moveRobotX:
	case GamepadCommands::moveRobotY: {
		auto config = manager->getConfig();
		manager->convertAndSendMovement(device->axisStates[config.getStickId(GamepadCommands::moveRobotX)], device->axisStates[config.getStickId(GamepadCommands::moveRobotY)]);
		break;
	}
	case GamepadCommands::moveCameraX: {
		manager->getTrackPlatformManager()->servoSetHorizontalAngle(static_cast<int>((value + 1) * 90));
		break;
	}
	case GamepadCommands::moveCameraY: {
		manager->getTrackPlatformManager()->servoSetVerticalAngle(static_cast<int>((value + 1) * 90));
		break;
	}
	default: break;
	}
}
