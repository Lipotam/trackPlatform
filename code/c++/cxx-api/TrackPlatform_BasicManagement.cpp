#include "TrackPlatform_BasicManagement.h"

void TrackPlatform_BasicManagement::sendMove(const std::string& additionalInfo) const
{
	connector->write(static_cast<char>(movementControllerID) + additionalInfo);
}

void TrackPlatform_BasicManagement::sendSensors(const std::string& additionalInfo) const
{
	connector->write(static_cast<char>(sensorsControllerID) + additionalInfo);
}

void TrackPlatform_BasicManagement::sendServo(const std::string& additionalInfo) const
{
	connector->write(static_cast<char>(servoControllerID) + additionalInfo);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::parseStringToArray(std::string s)
{
	std::vector<uint32_t> distancies;
	size_t stringOldLen = 0;
	size_t posToNextValue = 0;
	do
	{
		distancies.push_back(std::stoul(s, &posToNextValue));
		stringOldLen = s.length();
		s = s.substr(posToNextValue + sizeof delimiter);
	} while ((s != "") && (stringOldLen > s.length()));

	if (stringOldLen <= s.length())
	{
		distancies.pop_back();
	}
	return distancies;
}

TrackPlatform_BasicConnector* TrackPlatform_BasicManagement::getConnector() const
{
	return connector;
}

TrackPlatform_BasicManagement::TrackPlatform_BasicManagement(TrackPlatform_BasicConnector* connector)
	: connector(connector)
{
}

TrackPlatform_BasicManagement::~TrackPlatform_BasicManagement()
{
}

void TrackPlatform_BasicManagement::moveForward() const
{
	std::string toSend(1, forward);
	sendMove(toSend);
}

bool TrackPlatform_BasicManagement::moveForward(double speed) const
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, forward_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendMove(toSend);

	return true;
}

void TrackPlatform_BasicManagement::moveForward(uint32_t timeInMSec) const
{
	std::string toSend(1, forward_time);
	toSend += std::to_string(timeInMSec);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::moveBackward() const
{
	std::string toSend(1, back);
	sendMove(toSend);
}

bool TrackPlatform_BasicManagement::moveBackward(double speed) const
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, back_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendMove(toSend);

	return true;
}

void TrackPlatform_BasicManagement::rotateClockwise() const
{
	std::string toSend(1, right);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::rotateAntiClockwise() const
{
	std::string toSend(1, left);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::moveStopAll() const
{
	std::string toSend(1, stop);
	sendMove(toSend);
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
	sendMove(toSend);

	return true;
}

uint32_t TrackPlatform_BasicManagement::sensorDistanceGetValue(uint8_t num) const
{
	std::string toSend(1, distance_sensor);
	toSend += std::to_string(num);
	sendSensors(toSend);
	auto answer = connector->read();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorDistanceGetAllValues() const
{
	std::string toSend(1, distance_sensor_all);
	sendSensors(toSend);
	return parseStringToArray(connector->read());
}

uint32_t TrackPlatform_BasicManagement::sensorLineGetValue(uint8_t num) const
{
	std::string toSend(1, line_sensor);
	toSend += std::to_string(num);
	sendSensors(toSend);
	auto answer = connector->read();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorLineGetAllValues() const
{
	std::string toSend(1, line_sensor_all);
	sendSensors(toSend);
	return parseStringToArray(connector->read());
}

void TrackPlatform_BasicManagement::servoSetHorizontalAngle(uint16_t angle) const
{
	std::string toSend(1, set_horizontal_angle);
	toSend += std::to_string(angle);
	sendServo(toSend);
}

void TrackPlatform_BasicManagement::servoSetVerticalAngle(uint16_t angle) const
{
	std::string toSend(1, set_vertical_angle);
	toSend += std::to_string(angle);
	sendServo(toSend);
}

void TrackPlatform_BasicManagement::servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle) const
{
	std::string toSend(1, set_horiz_vertical_angles);
	toSend += std::to_string(horizontalAngle);
	toSend += delimiter;
	toSend += std::to_string(verticalAngle);
	sendServo(toSend);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::servoGetAngles() const
{
	std::string toSend(1, get_coodrinates);
	sendServo(toSend);
	return parseStringToArray(connector->read());
}
