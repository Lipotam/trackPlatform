#ifndef _GAMEPAD_MANAGER_H_
#define _GAMEPAD_MANAGER_H_

#include <thread>
#include <atomic>
#include "TrackPlatform_Manager.h"
#include "GamepadConfig.h"
#include "SensorsViewer.h"

class GamepadManager
{
	TrackPlatform_Manager* trackPlatform = nullptr;
	SensorsViewer* sensorsViewer = nullptr;
	/**
	 * @brief mutex is locked when handler thread is running, else not locked
	 */
	std::atomic_bool isRequireToRun = {false};
	/**
	 * @brief Handler thread pointer
	 */
	std::thread * runnedThread = nullptr;

	GamepadConfig config;

	static const double forwardMultiplier;

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
	/**
	* @brief Get current SensorsViewer
	* @return Current SensorsViewer
	*/
	SensorsViewer* getSensorsViewer() const;
	/**
	 * @brief Convert gamepad x and y values to movement speed of tracks and send it to device
	 * @param xValue X axis value (must be in interval [-1; 1])
	 * @param yValue Y axis value (must be in interval [-1; 1])
	 * @return true, if all were successed, else false
	 */
	bool convertAndSendMovement(double xValue, double yValue);
};

#endif /* _GAMEPAD_MANAGER_H_ */
