#include "TrackPlatform_BasicConnector.h"

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector(const std::string& rx, const std::string& tx, uint32_t baudRate) :
	rxLocation(rx), txLocation(tx), baudRate(baudRate)
{
}

TrackPlatform_BasicConnector::~TrackPlatform_BasicConnector()
{
}

std::string TrackPlatform_BasicConnector::readOneAnswer()
{
	return read();
}

void TrackPlatform_BasicConnector::sendOneCommand(const std::string& s)
{
	write(s + stopSymbol);
}
