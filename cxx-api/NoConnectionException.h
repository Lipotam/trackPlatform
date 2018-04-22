#ifndef _NO_CONNECTION_EXCEPTION_H_
#define _NO_CONNECTION_EXCEPTION_H_

#include "TrackPlatformException.h"

class NoConnectionException : public TrackPlatformException
{
public:
	explicit NoConnectionException() : TrackPlatformException()
	{
	}
};

#endif /* _NO_CONNECTION_EXCEPTION_H_ */
