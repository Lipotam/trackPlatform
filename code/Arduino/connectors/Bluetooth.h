#pragma once
#include "ConnectingDevice.h"

/**
 * @brief Bluetooth controller class
 * @attention Create first object of that class in setup() method only
 */
class Bluetooth : public ConnectingDevice
{
	/**
	 * @brief Block for double initialization
	 */
	static bool isInited;

public:
	Bluetooth();
	~Bluetooth();
};

