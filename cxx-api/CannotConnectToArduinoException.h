#ifndef _CANNOT_CONNECT_TO_ARDUINO_EXCEPTION_H_
#define _CANNOT_CONNECT_TO_ARDUINO_EXCEPTION_H_

#include "TrackPlatformException.h"

class CannotConnectToArduinoException : public TrackPlatformException
{
public:
	explicit CannotConnectToArduinoException() : TrackPlatformException()
	{
	}
};

#endif /* _CANNOT_CONNECT_TO_ARDUINO_EXCEPTION_H_ */
