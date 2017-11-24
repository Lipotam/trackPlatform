#pragma once

class TimeoutException : public TrackPlatformException
{
public:
	explicit TimeoutException() : TrackPlatformException()
	{
	}
};
