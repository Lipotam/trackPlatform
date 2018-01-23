#ifndef _TRACKPLATFORM_BASICMANAGEMENT_H_
#define _TRACKPLATFORM_BASICMANAGEMENT_H_

#include <vector>
#include <mutex>

#include "TrackPlatform_BasicConnector.h"
#include "CommandsEnum.h"

class TrackPlatform_BasicManagement
{
	TrackPlatform_BasicConnector* connector;

protected:
	static const uint8_t minSpeed = 0;
	static const uint8_t maxSpeed = 255;
	static const uint8_t minServoAngle = 0;
	static const uint8_t maxServoAngle = 180;
	static const char delimiter = ';';
	static const double minInputSpeed;
	static const double maxInputSpeed;

	std::string sendCommand(const ControllerEnum targetController, const std::string& additionalInfo, const bool isWaitAnswer = false);

	static std::vector<uint32_t> parseStringToArray(std::string s);

	TrackPlatform_BasicConnector* getConnector() const;

	/**
	 * \brief Send movement command to with connector
	 * \param command Command to send with speed
	 * \param speed Speed from @minSpeed to @maxSpeed interval
	 * \return true, if all is good, else false
	 */
	bool sendMovement(MoveEnum command, double speed);

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

	bool rotateClockwise(double speed = maxInputSpeed);
	bool rotateAntiClockwise(double speed = maxInputSpeed);

	void moveStopAll();

	//speed must be in [-1, 1] range
	bool setTrackForwardSpeed(TrackIndex trackId, double speed);
	//speed must be in [-1, 1] range
	bool setAllTrackForwardSpeed(double leftSpeed, double rightSpeed);

	/* sensors controller */
	uint32_t sensorDistanceGetValue(uint8_t num);
	std::vector<uint32_t> sensorDistanceGetAllValues();
	uint32_t sensorLineGetValue(uint8_t num);
	std::vector<uint32_t> sensorLineGetAllValues();
	uint32_t sensorDistanceGetRawValue(uint8_t num);
	std::vector<uint32_t> sensorDistanceGetAllRawValues();
	uint32_t sensorLineGetRawValue(uint8_t num);
	std::vector<uint32_t> sensorLineGetAllRawValues();

	/* servo controller */
	void servoSetHorizontalAngle(uint16_t angle);
	void servoSetVerticalAngle(uint16_t angle);
	void servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle);
	std::vector<uint32_t> servoGetAngles();
	//angle must be in [0, 180] range
	bool servoSetAngle(ServoIndex axisIndex, uint16_t angle);
	uint16_t servoGetAngle(ServoIndex axisIndex);
};

#endif /* _TRACKPLATFORM_BASICMANAGEMENT_H_ */
