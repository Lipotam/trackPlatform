#pragma once
#include "SocketException.h"

class SocketShutdownException : public SocketException
{
public:
	explicit SocketShutdownException(int errorCode)
		: SocketException(errorCode)
	{
	}
};
