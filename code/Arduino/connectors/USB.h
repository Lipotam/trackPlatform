#pragma once

#include "ConnectingDevice.h"

/**
 * @brief USB controller class
 * @attention Create first object of that class in setup() method only
 */
class USB : public ConnectingDevice
{
	/**
	 * @brief Block for double initialization
	 */
	static bool isInited;

public:
	explicit USB(unsigned long speed);
	~USB();
};
