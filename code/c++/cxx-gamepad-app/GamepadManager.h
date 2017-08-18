#ifndef _GAMEPAD_MANAGER_H_
#define _GAMEPAD_MANAGER_H_

#include <mutex>
#include "TrackPlatform_Manager.h"
#include "GamepadConfig.h"

class GamepadManager
{
	TrackPlatform_Manager* trackPlatform = nullptr;
	/**
	 * @brief mutex is locked when handler thread is running, else not locked
	 */
	std::mutex * isRunningNow = nullptr;
	/**
	 * @brief Handler thread pointer
	 */
	std::thread * runnedThread = nullptr;

	GamepadConfig config;

public:
	GamepadManager(TrackPlatform_Manager* trackPlatform);
	~GamepadManager();
	/**
	 * @brief Run gamepad handler thread
	 */
	void run();
	/**
	 * @brief Stop gamepad handler thread
	 */
	void stop();
	/**
	 * @brief Wait while handler thread not stopped
	 */
	void join();
	/**
	 * @brief Get current gamepad config
	 * @return Current gamepad configuration
	 */
	const GamepadConfig& getConfig() const;
	/**
	 * @brief Get current trackPlatform manager
	 * @return Current trackPlatform manager
	 */
	TrackPlatform_Manager* getTrackPlatformManager() const;
};

#endif /* _GAMEPAD_MANAGER_H_ */
