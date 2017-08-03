#ifndef _TRACKPLATFORM_BASICMANAGEMENT_H_
#define _TRACKPLATFORM_BASICMANAGEMENT_H_

#include <vector>

#include "TrackPlatform_BasicConnector.h"
#include "CommandsEnum.h"

class TrackPlatform_BasicManagement
{
	TrackPlatform_BasicConnector* connector;

	static const uint8_t minSpeed = 0;
	static const uint8_t maxSpeed = 255;
	static const char delimiter = ';';

protected:
	void sendMove(const std::string& additionalInfo) const;
	void sendSensors(const std::string& additionalInfo) const;
	void sendServo(const std::string& additionalInfo) const;

	static std::vector<uint32_t> parseStringToArray(std::string s);

	TrackPlatform_BasicConnector* getConnector() const;

public:
	TrackPlatform_BasicManagement(TrackPlatform_BasicConnector* connector);
	virtual ~TrackPlatform_BasicManagement();

	/* movement controller */
	void moveForward() const;
	//speed must be in [0,1] range
	bool moveForward(double speed) const;
	void moveForward(uint32_t timeInMSec) const;

	void moveBackward() const;
	//speed must be in [0,1] range
	bool moveBackward(double speed) const;

	void rotateClockwise() const;
	void rotateAntiClockwise() const;

	void moveStopAll() const;

	//speed must be in [0,1] range
	bool setTrackForwardSpeed(TrackID trackId, double speed) const;

	/* sensors controller */
	uint32_t sensorDistanceGetValue(uint8_t num) const;
	std::vector<uint32_t> sensorDistanceGetAllValues() const;
	uint32_t sensorLineGetValue(uint8_t num) const;
	std::vector<uint32_t> sensorLineGetAllValues() const;

	/* servo controller */
	void servoSetHorizontalAngle(uint16_t angle) const;
	void servoSetVerticalAngle(uint16_t angle) const;
	void servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle) const;
	std::vector<uint32_t> servoGetAngles() const;
};

#endif /* _TRACKPLATFORM_BASICMANAGEMENT_H_ */
