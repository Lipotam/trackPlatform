#include "TrackPlatform_BasicManagement.h"

std::string TrackPlatform_BasicManagement::sendCommand(const ControllerEnum targetController, const std::string& additionalInfo, const bool isWaitAnswer)
{
	readWriteAtomicMutex.lock();
	std::string answer = connector->sendOneCommand(static_cast<char>(targetController) + additionalInfo, isWaitAnswer);
	readWriteAtomicMutex.unlock();
	return answer;
}

std::vector<uint32_t> TrackPlatform_BasicManagement::parseStringToArray(std::string s)
{
	std::vector<uint32_t> distancies;
	size_t stringOldLen = 0;
	size_t posToNextValue = 0;
	try
	{
		do
		{

			distancies.push_back(std::stoul(s, &posToNextValue));
			stringOldLen = s.length();
			s = s.substr(posToNextValue + sizeof delimiter);

		} while ((s != "") && (stringOldLen > s.length()));
	}
	catch (...)
	{
		return distancies;
	}

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

void TrackPlatform_BasicManagement::moveForward()
{
	std::string toSend(1, forward);
	sendCommand(movementControllerID, toSend);
}

bool TrackPlatform_BasicManagement::moveForward(double speed)
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, forward_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendCommand(movementControllerID, toSend);

	return true;
}

void TrackPlatform_BasicManagement::moveForward(uint32_t timeInMSec)
{
	std::string toSend(1, forward_time);
	toSend += std::to_string(timeInMSec);
	sendCommand(movementControllerID, toSend);
}

void TrackPlatform_BasicManagement::moveBackward()
{
	std::string toSend(1, back);
	sendCommand(movementControllerID, toSend);
}

bool TrackPlatform_BasicManagement::moveBackward(double speed)
{
	if (speed < 0 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, back_speed);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendCommand(movementControllerID, toSend);

	return true;
}

void TrackPlatform_BasicManagement::rotateClockwise()
{
	std::string toSend(1, right);
	sendCommand(movementControllerID, toSend);
}

void TrackPlatform_BasicManagement::rotateAntiClockwise()
{
	std::string toSend(1, left);
	sendCommand(movementControllerID, toSend);
}

void TrackPlatform_BasicManagement::moveStopAll()
{
	std::string toSend(1, stop);
	sendCommand(movementControllerID, toSend);
}

bool TrackPlatform_BasicManagement::setTrackForwardSpeed(TrackIndex trackId, double speed)
{
	if (speed < -1 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, track_set_speed);
	toSend += std::to_string(*reinterpret_cast<const uint8_t*>(&trackId));
	toSend += delimiter;
	toSend += std::to_string(static_cast<int16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendCommand(movementControllerID, toSend);

	return true;
}

uint32_t TrackPlatform_BasicManagement::sensorDistanceGetValue(uint8_t num)
{
	std::string toSend(1, distance_sensor);
	toSend += std::to_string(num);
	readWriteAtomicMutex.lock();
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	readWriteAtomicMutex.unlock();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorDistanceGetAllValues()
{
	std::string toSend(1, distance_sensor_all);
	readWriteAtomicMutex.lock();
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}

uint32_t TrackPlatform_BasicManagement::sensorLineGetValue(uint8_t num)
{
	std::string toSend(1, line_sensor);
	toSend += std::to_string(num);
	readWriteAtomicMutex.lock();
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	readWriteAtomicMutex.unlock();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorLineGetAllValues()
{
	std::string toSend(1, line_sensor_all);
	readWriteAtomicMutex.lock();
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}

void TrackPlatform_BasicManagement::servoSetHorizontalAngle(uint16_t angle)
{
	std::string toSend(1, set_horizontal_angle);
	toSend += std::to_string(angle);
	const std::string answer = sendCommand(servoControllerID, toSend);
}

void TrackPlatform_BasicManagement::servoSetVerticalAngle(uint16_t angle)
{
	std::string toSend(1, set_vertical_angle);
	toSend += std::to_string(angle);
	const std::string answer = sendCommand(servoControllerID, toSend);
}

void TrackPlatform_BasicManagement::servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle)
{
	std::string toSend(1, set_horiz_vertical_angles);
	toSend += std::to_string(horizontalAngle);
	toSend += delimiter;
	toSend += std::to_string(verticalAngle);
	const std::string answer = sendCommand(servoControllerID, toSend);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::servoGetAngles()
{
	std::string toSend(1, get_coodrinates);
	readWriteAtomicMutex.lock();
	const std::string answer = sendCommand(servoControllerID, toSend, true);
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}
