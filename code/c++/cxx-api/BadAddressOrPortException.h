#ifndef _BAD_ADDRESS_OR_PORT_EXCEPTION_H_
#define _BAD_ADDRESS_OR_PORT_EXCEPTION_H_

#include "TrackPlatformException.h"

class BadAddressOrPortException : public TrackPlatformException
{
public:
	explicit BadAddressOrPortException(int errorCode) : TrackPlatformException(std::to_string(errorCode))
	{
	}
};

#endif /* _BAD_ADDRESS_OR_PORT_EXCEPTION_H_ */
