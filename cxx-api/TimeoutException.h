#pragma once

#include "TrackPlatformException.h"

class TimeoutException : public TrackPlatformException
{
public:
	explicit TimeoutException() : TrackPlatformException()
	{
	}
};
