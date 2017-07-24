#ifndef _TRACKPLATFORM_BASICMANAGEMENT_H_
#define _TRACKPLATFORM_BASICMANAGEMENT_H_

#include "TrackPlatform_BasicConnector.h"
#include "CommandsEnum.h"

class TrackPlatform_BasicManagement
{
	TrackPlatform_BasicConnector* connector;
	
	static const uint8_t minSpeed = 0;
	static const uint8_t maxSpeed = 255;
	static const char delimiter = ';';

protected:
	void move(const std::string& additionalInfo) const;

public:
	TrackPlatform_BasicManagement(TrackPlatform_BasicConnector* connector);

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
};

#endif /* _TRACKPLATFORM_BASICMANAGEMENT_H_ */
