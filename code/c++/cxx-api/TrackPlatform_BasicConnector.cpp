#include "TrackPlatform_BasicConnector.h"
#include "Logger.h"

TrackPlatform_BasicConnector::TrackPlatform_BasicConnector() 
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
	Logger::log("Send: " + s + stopSymbol);
}
