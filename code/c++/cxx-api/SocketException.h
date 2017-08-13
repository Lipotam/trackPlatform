#pragma once
#include "TrackPlatformException.h"

class SocketException : public TrackPlatformException
{
public:
	explicit SocketException(int errorCode) : TrackPlatformException(std::to_string(errorCode))
	{
	}
};
