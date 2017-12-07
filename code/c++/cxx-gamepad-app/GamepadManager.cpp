#include <atomic>
#include "TrackPlatform_Manager.h"
#include "gamepad/Gamepad.h"
#include "gamepad_callbacks.h"

#include "GamepadManager.h"

const double GamepadManager::forwardMaxSpeed = 0.6;
const double GamepadManager::rotateMaxSpeed = 0.6;

GamepadManager::GamepadManager(TrackPlatform_Manager* trackPlatform) : trackPlatform(trackPlatform), sensorsViewer(new SensorsViewer), runnedThread(nullptr)
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
	if (sensorsViewer)
	{
		delete sensorsViewer;
	}
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

SensorsViewer* GamepadManager::getSensorsViewer() const
{
	return sensorsViewer;
}

bool GamepadManager::convertAndSendMovement(double xValue, double yValue)
{
	if (!trackPlatform || (xValue > 1) || (xValue < -1) || (yValue > 1) || (yValue < -1))
	{
		return false;
	}

	double leftTrackSpeed = yValue * forwardMaxSpeed + xValue * rotateMaxSpeed;
	double rightTrackSpeed = yValue * forwardMaxSpeed - xValue * rotateMaxSpeed;

	//calibrating values
	auto catibrator = [](double current, double min, double max) -> double 
	{
		return ((current > max) ? max : ((current < min) ? min : current));
	};
	leftTrackSpeed = catibrator(leftTrackSpeed, -1, 1);
	rightTrackSpeed = catibrator(rightTrackSpeed, -1, 1);

	if (!trackPlatform->setAllTrackForwardSpeed(leftTrackSpeed, rightTrackSpeed))
	{
		return false;
	}

	return true;
}
