#ifndef _TRACKPLATFORM_BASICCONNECTOR_H_
#define _TRACKPLATFORM_BASICCONNECTOR_H_

#include <string>

class TrackPlatform_BasicConnector
{
protected:
	static const char stopSymbol = '|';

	virtual void write(const std::string& s) = 0;
	virtual std::string read() = 0;

public:
	TrackPlatform_BasicConnector();
	virtual ~TrackPlatform_BasicConnector();

	/**
	 * @brief Read only one answer
	 * @warning By default returns one portion of data from rx, must be overriden if require
	 */
	virtual std::string readOneAnswer();
	virtual void sendOneCommand(const std::string& s);
	virtual bool isConnected() = 0;
};

#endif /* _TRACKPLATFORM_BASICCONNECTOR_H_ */
