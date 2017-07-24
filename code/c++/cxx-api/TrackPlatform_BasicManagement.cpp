#include "TrackPlatform_BasicManagement.h"

void TrackPlatform_BasicManagement::move(const std::string& additionalInfo) const
{
	connector->write(static_cast<char>(movementControllerID) + additionalInfo);
}

TrackPlatform_BasicManagement::TrackPlatform_BasicManagement(TrackPlatform_BasicConnector* connector)
	: connector(connector)
{
}

void TrackPlatform_BasicManagement::moveForward() const
{
	std::string toSend(1, forward);
	move(toSend);
}

bool TrackPlatform_BasicManagement::moveForward(double speed) const
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, forward_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	move(toSend);

	return true;
}

void TrackPlatform_BasicManagement::moveForward(uint32_t timeInMSec) const
{
	std::string toSend(1, forward_time);
	toSend += std::to_string(timeInMSec);
	move(toSend);
}

void TrackPlatform_BasicManagement::moveBackward() const
{
	std::string toSend(1, back);
	move(toSend);
}

bool TrackPlatform_BasicManagement::moveBackward(double speed) const
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, back_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	move(toSend);

	return true;
}

void TrackPlatform_BasicManagement::rotateClockwise() const
{
	std::string toSend(1, right);
	move(toSend);
}

void TrackPlatform_BasicManagement::rotateAntiClockwise() const
{
	std::string toSend(1, left);
	move(toSend);
}

void TrackPlatform_BasicManagement::moveStopAll() const
{
	std::string toSend(1, stop);
	move(toSend);
}

bool TrackPlatform_BasicManagement::setTrackForwardSpeed(TrackID trackId, double speed) const
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, back_speed);
	toSend += std::to_string(*reinterpret_cast<const uint8_t*>(&trackId));
	toSend += delimiter;
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	move(toSend);

	return true;
}
