#ifndef _TRACKPLATFORM_BASICCONNECTOR_H_
#define _TRACKPLATFORM_BASICCONNECTOR_H_

#include <string>

class TrackPlatform_BasicConnector
{
	std::string rxLocation;
	std::string txLocation;
	uint32_t baudRate;

public:
	TrackPlatform_BasicConnector(const std::string& rx, const std::string& tx, uint32_t baudRate);
	virtual ~TrackPlatform_BasicConnector() = 0;

	virtual std::string read() = 0;
	virtual void write(const std::string& s) = 0;
	virtual bool isAvailable() = 0;
};

#endif /* _TRACKPLATFORM_BASICCONNECTOR_H_ */
