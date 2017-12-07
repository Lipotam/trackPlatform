#pragma once
#include "TrackPlatform_Manager.h"

class ConsolePlatformConnector
{
public:
	TrackPlatform_Manager* connect();

private:
	TrackPlatform_Manager* connectBySerial();
	TrackPlatform_Manager* connectByTcpIp();
};
