#ifndef _WSA_STARTUP_EXCEPTION_H_
#define _WSA_STARTUP_EXCEPTION_H_

#include "TrackPlatformException.h"

class WSAStartupException : public TrackPlatformException
{
public:
	explicit WSAStartupException(int errorCode) : TrackPlatformException(std::to_string(errorCode))
	{
	}
};

#endif /* _WSA_STARTUP_EXCEPTION_H_ */
