#pragma once
#include "TrackPlatform_BasicConnector.h"

class StreamConnector : public TrackPlatform_BasicConnector
{
	std::string buffer;

protected:
	virtual std::string streamRead(uint64_t size = 1) = 0;
	virtual uint64_t streamAvailable() = 0;
	std::string read() override;
};
