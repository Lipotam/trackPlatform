#include "TrackPlatform_Manager.h"
#include "gamepad/Gamepad.h"
#include "gamepad_callbacks.h"

#include "GamepadManager.h"

const double GamepadManager::forwardMultiplier = 0.6;

GamepadManager::GamepadManager(TrackPlatform_Manager* trackPlatform) : trackPlatform(trackPlatform), runnedThread(nullptr)
{
	Gamepad_buttonDownFunc(onButtonDown, (void *)this);
	Gamepad_buttonUpFunc(onButtonUp, (void *)this);
	Gamepad_axisMoveFunc(onAxisMoved, (void *)this);
	Gamepad_init();
}

GamepadManager::~GamepadManager()
{
	stop();
	join();
	if (runnedThread)
	{
		delete runnedThread;
	}
	Gamepad_shutdown();
}

void GamepadManager::run()
{
	isRequireToRun = true;

	runnedThread = runnedThread ? runnedThread : new std::thread([this]()
	{
		while (this->isRequireToRun)
		{
			Gamepad_detectDevices();
			Gamepad_processEvents();
		}
	});
}

void GamepadManager::stop()
{
	isRequireToRun = false;
}

void GamepadManager::join()
{
	if (!runnedThread)
	{
		return;
	}

	if (runnedThread->joinable())
	{
		runnedThread->join();
	}
	delete runnedThread;
	runnedThread = nullptr;
}

const GamepadConfig& GamepadManager::getConfig() const
{
	return config;
}

TrackPlatform_Manager* GamepadManager::getTrackPlatformManager() const
{
	return trackPlatform;
}

bool GamepadManager::convertAndSendMovement(double xValue, double yValue)
{
	if (!trackPlatform || (xValue > 1) || (xValue < -1) || (yValue > 1) || (yValue < -1))
	{
		return false;
	}

	if (!trackPlatform->setTrackForwardSpeed(left_track, yValue * forwardMultiplier - xValue * (1 - forwardMultiplier)))
	{
		return false;
	}

	if (!trackPlatform->setTrackForwardSpeed(right_track, yValue * forwardMultiplier + xValue * (1 - forwardMultiplier)))
	{
		return false;
	}

	return true;
}
