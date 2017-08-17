#ifndef _GAMEPAD_MANAGER_H_
#define _GAMEPAD_MANAGER_H_

#include "TrackPlatform_Manager.h"

class GamepadManager
{
	TrackPlatform_Manager* trackPlatform = nullptr;
	bool * isNeedToExit = nullptr;
public:
	GamepadManager(TrackPlatform_Manager* trackPlatform);
	~GamepadManager();
	void run();
};

#endif /* _GAMEPAD_MANAGER_H_ */
