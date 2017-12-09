#pragma once

#include <vector>

enum SensorType {
	LINE_SENSORS, DISTANCE_SENSORS
};

class SensorsViewer {
protected:
	std::vector<uint32_t> lineSensors;
	std::vector<uint32_t> distanceSensors;

	virtual void showDistanceInfo();
	virtual void showLineInfo();

public:
	void setData(const std::vector<uint32_t>& d, SensorType t);
	void show();
	void show(SensorType type);
};
