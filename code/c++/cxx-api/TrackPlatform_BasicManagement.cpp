#include "TrackPlatform_BasicManagement.h"

void TrackPlatform_BasicManagement::sendMove(const std::string& additionalInfo)
{
	readWriteAtomicMutex.lock();
	connector->sendOneCommand(static_cast<char>(movementControllerID) + additionalInfo);
	readWriteAtomicMutex.unlock();
}

void TrackPlatform_BasicManagement::sendSensors(const std::string& additionalInfo)
{
	readWriteAtomicMutex.lock();
	connector->sendOneCommand(static_cast<char>(sensorsControllerID) + additionalInfo);
	readWriteAtomicMutex.unlock();
}

void TrackPlatform_BasicManagement::sendServo(const std::string& additionalInfo)
{
	readWriteAtomicMutex.lock();
	connector->sendOneCommand(static_cast<char>(servoControllerID) + additionalInfo);
	readWriteAtomicMutex.unlock();
}

void TrackPlatform_BasicManagement::sendCommunication(const std::string& additionalInfo) {
	readWriteAtomicMutex.lock();
	connector->sendOneCommand(static_cast<char>(communicationControllerID) + additionalInfo);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
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
	sendMove(toSend);
}

bool TrackPlatform_BasicManagement::moveForward(double speed)
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

void TrackPlatform_BasicManagement::moveForward(uint32_t timeInMSec)
{
	std::string toSend(1, forward_time);
	toSend += std::to_string(timeInMSec);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::moveBackward()
{
	std::string toSend(1, back);
	sendMove(toSend);
}

bool TrackPlatform_BasicManagement::moveBackward(double speed)
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

void TrackPlatform_BasicManagement::rotateClockwise()
{
	std::string toSend(1, right);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::rotateAntiClockwise()
{
	std::string toSend(1, left);
	sendMove(toSend);
}

void TrackPlatform_BasicManagement::moveStopAll()
{
	std::string toSend(1, stop);
	sendMove(toSend);
}

bool TrackPlatform_BasicManagement::setTrackForwardSpeed(TrackID trackId, double speed)
{
	if (speed < -1 || speed > 1)
	{
		return false;
	}

	std::string toSend(1, track_set_speed);
	toSend += std::to_string(*reinterpret_cast<const uint8_t*>(&trackId));
	toSend += delimiter;
	toSend += std::to_string(static_cast<int16_t>(speed * (maxSpeed - minSpeed) + minSpeed));
	sendMove(toSend);

	return true;
}

uint32_t TrackPlatform_BasicManagement::sensorDistanceGetValue(uint8_t num)
{
	std::string toSend(1, distance_sensor);
	toSend += std::to_string(num);
	readWriteAtomicMutex.lock();
	sendSensors(toSend);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorDistanceGetAllValues()
{
	std::string toSend(1, distance_sensor_all);
	readWriteAtomicMutex.lock();
	sendSensors(toSend);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}

uint32_t TrackPlatform_BasicManagement::sensorLineGetValue(uint8_t num)
{
	std::string toSend(1, line_sensor);
	toSend += std::to_string(num);
	readWriteAtomicMutex.lock();
	sendSensors(toSend);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
	return std::stoi(answer);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::sensorLineGetAllValues()
{
	std::string toSend(1, line_sensor_all);
	readWriteAtomicMutex.lock();
	sendSensors(toSend);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}

void TrackPlatform_BasicManagement::servoSetHorizontalAngle(uint16_t angle)
{
	std::string toSend(1, set_horizontal_angle);
	toSend += std::to_string(angle);
	sendServo(toSend);
}

void TrackPlatform_BasicManagement::servoSetVerticalAngle(uint16_t angle)
{
	std::string toSend(1, set_vertical_angle);
	toSend += std::to_string(angle);
	sendServo(toSend);
}

void TrackPlatform_BasicManagement::servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle)
{
	std::string toSend(1, set_horiz_vertical_angles);
	toSend += std::to_string(horizontalAngle);
	toSend += delimiter;
	toSend += std::to_string(verticalAngle);
	sendServo(toSend);
}

std::vector<uint32_t> TrackPlatform_BasicManagement::servoGetAngles()
{
	std::string toSend(1, get_coodrinates);
	readWriteAtomicMutex.lock();
	sendServo(toSend);
	auto answer = connector->readOneAnswer();
	readWriteAtomicMutex.unlock();
	return parseStringToArray(answer);
}

void TrackPlatform_BasicManagement::refreshConnection() {
	std::string toSend(1, refreshConnectionCommunicationCommand);
	sendCommunication(toSend);
}