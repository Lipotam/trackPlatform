#include "TrackPlatform_BasicManagement.h"

const double TrackPlatform_BasicManagement::minInputSpeed = -1;
const double TrackPlatform_BasicManagement::maxInputSpeed = 1;

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

bool TrackPlatform_BasicManagement::sendMovement(const MoveEnum command, const double speed)
{
	if (speed < minInputSpeed || speed > maxInputSpeed)
	{
		return false;
	}

	std::string toSend(1, command);
	toSend += std::to_string(static_cast<uint16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendCommand(movementControllerID, toSend);

	return true;
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
	moveForward(maxInputSpeed);
}

bool TrackPlatform_BasicManagement::moveForward(double speed)
{
	return sendMovement(forward_speed, speed);
}

void TrackPlatform_BasicManagement::moveForward(uint32_t timeInMSec)
{
	moveForward(maxInputSpeed);
	std::this_thread::sleep_for(std::chrono::milliseconds(timeInMSec));
	moveStopAll();
}

void TrackPlatform_BasicManagement::moveBackward()
{
	moveForward(-maxInputSpeed);
}

bool TrackPlatform_BasicManagement::moveBackward(double speed)
{
	return moveForward(-speed);
}

bool TrackPlatform_BasicManagement::rotateClockwise(double speed)
{
	return sendMovement(clockwise, speed);
}

bool TrackPlatform_BasicManagement::rotateAntiClockwise(double speed)
{
	return rotateClockwise(-speed);
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
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorDistanceGetAllValues()
{
	std::string toSend(1, distance_sensor_all);
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	return parseStringToArray(answer);
}

uint32_t TrackPlatform_BasicManagement::sensorLineGetValue(uint8_t num)
{
	std::string toSend(1, line_sensor);
	toSend += std::to_string(num);
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorLineGetAllValues()
{
	std::string toSend(1, line_sensor_all);
	const std::string answer = sendCommand(sensorsControllerID, toSend, true);
	return parseStringToArray(answer);
}

void TrackPlatform_BasicManagement::servoSetHorizontalAngle(uint16_t angle)
{
	servoSetAngle(xy_plane, angle);
}

void TrackPlatform_BasicManagement::servoSetVerticalAngle(uint16_t angle)
{
	servoSetAngle(xz_plane, angle);
}

void TrackPlatform_BasicManagement::servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle)
{
	servoSetAngle(xy_plane, horizontalAngle);
	servoSetAngle(xz_plane, verticalAngle);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::servoGetAngles()
{
	std::vector<uint32_t> answer;
	answer.push_back(servoGetAngle(xy_plane));
	answer.push_back(servoGetAngle(xz_plane));
	return answer;
}

bool TrackPlatform_BasicManagement::servoSetAngle(ServoIndex axisIndex, uint16_t angle)
{
	if (angle < minServoAngle || angle > maxServoAngle)
	{
		return false;
	}

	std::string toSend(1, set_angle);
	toSend += std::to_string(*reinterpret_cast<const uint8_t*>(&axisIndex));
	toSend += delimiter;
	toSend += std::to_string(angle);
	sendCommand(servoControllerID, toSend);
	return true;
}

uint16_t TrackPlatform_BasicManagement::servoGetAngle(ServoIndex axisIndex)
{
	std::string toSend(1, get_angle);
	toSend += std::to_string(*reinterpret_cast<const uint8_t*>(&axisIndex));
	const std::string answer = sendCommand(servoControllerID, toSend, true);
	return std::stoi(answer);
}
