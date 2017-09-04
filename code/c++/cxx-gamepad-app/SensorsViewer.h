#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iomanip>

enum SensorType {
	LINE_SENSORS, DISTANCE_SENSORS
};

class SensorsViewer {
	std::vector<uint32_t> lineSensors;
	std::vector<uint32_t> distanceSensors;

	void showDistanceInfo();
	void showLineInfo();

public:
	void setData(const std::vector<uint32_t>& d, SensorType t);
	void show();
	void show(SensorType type);
};