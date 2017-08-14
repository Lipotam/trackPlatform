#ifndef _SOCKET_EXCEPTION_H_
#define _SOCKET_EXCEPTION_H_
#include "TrackPlatformException.h"

class SocketException : public TrackPlatformException
{
public:
	explicit SocketException(int errorCode) : TrackPlatformException(std::to_string(errorCode))
	{
	}
};

#endif /* _SOCKET_EXCEPTION_H_ */
