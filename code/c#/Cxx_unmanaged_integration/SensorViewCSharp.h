#pragma once
#include "SensorsViewer.h"
#include "integration.h"

class SensorViewCSharp : public SensorsViewer
{
	sensor_callback lineCallback = nullptr;
	sensor_callback distanceCallback = nullptr;

protected:
	void showDistanceInfo() override;
	void showLineInfo() override;

public:
	void setLineCallback(sensor_callback callback);
	void setDistanceCallback(sensor_callback callback);
};
