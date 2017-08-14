#ifndef _SOCKET_SEND_EXCETION_H_
#define _SOCKET_SEND_EXCETION_H_
#include "SocketException.h"

class SocketSendException : public SocketException
{
public:
	explicit SocketSendException(int errorCode)
		: SocketException(errorCode)
	{
	}
};

#endif /* _SOCKET_SEND_EXCETION_H_ */
