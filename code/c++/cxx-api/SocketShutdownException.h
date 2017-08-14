#ifndef _SOCKET_SHUTDOWN_EXCEPTION_H_
#define _SOCKET_SHUTDOWN_EXCEPTION_H_
#include "SocketException.h"

class SocketShutdownException : public SocketException
{
public:
	explicit SocketShutdownException(int errorCode)
		: SocketException(errorCode)
	{
	}
};

#endif /* _SOCKET_SHUTDOWN_EXCEPTION_H_ */
