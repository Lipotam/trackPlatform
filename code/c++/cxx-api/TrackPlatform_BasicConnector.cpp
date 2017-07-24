#include "TrackPlatform_BasicConnector.h"

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	rxLocation(rx), txLocation(tx), baudRate(baudRate)
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}
