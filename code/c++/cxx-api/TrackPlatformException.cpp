#include "TrackPlatformException.h"

TrackPlatformException::TrackPlatformException()
{
}

TrackPlatformException::TrackPlatformException(const std::string& errorMessage)
	: std::exception(errorMessage.c_str())
{
}
