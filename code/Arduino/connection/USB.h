#pragma once

#include "IConnector.h"

/**
 * @brief USB controller class
 * @attention Create first object of that class in setup() method only
 */
class USB : public IConnector
{
	/**
	 * @brief Block for double initialization
	 */
	static bool is_inited_;

public:
	explicit USB(unsigned long speed);
	~USB();
};
