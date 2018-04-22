#ifndef _SOCKET_RECEIVE_EXCEPTION_H_
#define _SOCKET_RECEIVE_EXCEPTION_H_
#include "SocketException.h"

class SocketReceiveException : public SocketException
{
public:
	explicit SocketReceiveException(int errorCode)
		: SocketException(errorCode)
	{
	}
};

#endif /* _SOCKET_RECEIVE_EXCEPTION_H_ */
