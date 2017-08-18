#include "TrackPlatform_Manager.h"
#include "gamepad/Gamepad.h"
#include "gamepad_callbacks.h"

#include "GamepadManager.h"

GamepadManager::GamepadManager(TrackPlatform_Manager* trackPlatform) : trackPlatform(trackPlatform), isRunningNow(new std::mutex), runnedThread(nullptr)
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
	if (isRunningNow)
	{
		delete isRunningNow;
	}
	if (runnedThread)
	{
		delete runnedThread;
	}
	Gamepad_shutdown();
}

void GamepadManager::run()
{
	runnedThread = runnedThread ? runnedThread : new std::thread([this]()
	{
		while (this->isRunningNow && !this->isRunningNow->try_lock())
		{
			Gamepad_detectDevices();
			Gamepad_processEvents();
		}

		this->isRunningNow->unlock();
	});
}

void GamepadManager::stop()
{
	//TODO
}

void GamepadManager::join()
{
	//TODO
}

const GamepadConfig& GamepadManager::getConfig() const
{
	return config;
}

TrackPlatform_Manager* GamepadManager::getTrackPlatformManager() const
{
	return trackPlatform;
}

}
