#pragma once
#include "IConnector.h"

/**
 * @brief Bluetooth controller class
 * @attention Create first object of that class in setup() method only
 */
class Bluetooth : public IConnector
{
	/**
	 * @brief Block for double initialization
	 */
	static bool is_inited_;

public:
	explicit Bluetooth(unsigned long speed);
	~Bluetooth();
};

