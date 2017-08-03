﻿#ifndef _TRACKPLATFORM_BASICCONNECTOR_H_
#define _TRACKPLATFORM_BASICCONNECTOR_H_

#include <string>

class TrackPlatform_BasicConnector
{
protected:
	std::string rxLocation;
	std::string txLocation;
	uint32_t baudRate;

	static const char stopSymbol = '|';

	virtual void write(const std::string& s) = 0;
	virtual std::string read() = 0;

    void sendStartCommand();
    void sendStopCommand();

public:
	TrackPlatform_BasicConnector(const std::string& rx, const std::string& tx, uint32_t baudRate);
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