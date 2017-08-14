#ifndef _TRACK_PLATFORM_EXCEPTION_H_
#define _TRACK_PLATFORM_EXCEPTION_H_

#include <exception>
#include <string>

class TrackPlatformException : public std::exception
{
public:
	TrackPlatformException();
	explicit TrackPlatformException(const std::string& errorMessage);
};

#endif /* _TRACK_PLATFORM_EXCEPTION_H_ */
