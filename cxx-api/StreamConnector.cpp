#include <algorithm>
#include "trackPlatformAllExceptions.h"

#include "StreamConnector.h"

std::string StreamConnector::read()
{
	if (buffer.empty())
	{
		buffer += streamRead(sizeof(uint8_t));
	}
	if (buffer.empty())
	{
		throw TimeoutException();
	}
	const uint8_t len = buffer[0];
	const uint16_t substring_len = sizeof(len) + len + crc_length;
	if ((substring_len) > buffer.length())
	{
		buffer += streamRead(std::max(substring_len - sizeof(len), streamAvailable()));
	}

	if ((substring_len) > buffer.length())
	{
		throw TimeoutException();
	}

	std::string answer = buffer.substr(0, substring_len);
	buffer.erase(0, substring_len);

	return answer;
}
