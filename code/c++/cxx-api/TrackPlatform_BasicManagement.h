#ifndef _TRACKPLATFORM_BASICMANAGEMENT_H_
#define _TRACKPLATFORM_BASICMANAGEMENT_H_

#include <vector>
#include <mutex>

#include "TrackPlatform_BasicConnector.h"
#include "CommandsEnum.h"

class TrackPlatform_BasicManagement
{
	TrackPlatform_BasicConnector* connector;

	static const uint8_t minSpeed = 0;
	static const uint8_t maxSpeed = 255;
	static const char delimiter = ';';

protected:
	void sendMove(const std::string& additionalInfo);
	void sendSensors(const std::string& additionalInfo);
	void sendServo(const std::string& additionalInfo);
	void sendCommunication(const std::string& additionalInfo);

	static std::vector<uint32_t> parseStringToArray(std::string s);

	TrackPlatform_BasicConnector* getConnector() const;

	std::recursive_mutex readWriteAtomicMutex;

public:
	TrackPlatform_BasicManagement(TrackPlatform_BasicConnector* connector);
	virtual ~TrackPlatform_BasicManagement();

	/* movement controller */
	void moveForward();
	//speed must be in [0,1] range
	bool moveForward(double speed);
	void moveForward(uint32_t timeInMSec);

	void moveBackward();
	//speed must be in [0,1] range
	bool moveBackward(double speed);

	void rotateClockwise();
	void rotateAntiClockwise();

	void moveStopAll();

	//speed must be in [-1, 1] range
	bool setTrackForwardSpeed(TrackID trackId, double speed);

	/* sensors controller */
	uint32_t sensorDistanceGetValue(uint8_t num);
	std::vector<uint32_t> sensorDistanceGetAllValues();
	uint32_t sensorLineGetValue(uint8_t num);
	std::vector<uint32_t> sensorLineGetAllValues();

	/* servo controller */
	void servoSetHorizontalAngle(uint16_t angle);
	void servoSetVerticalAngle(uint16_t angle);
	void servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle);
	std::vector<uint32_t> servoGetAngles();
	
	/* connection */
	void refreshConnection();
};

#endif /* _TRACKPLATFORM_BASICMANAGEMENT_H_ */
