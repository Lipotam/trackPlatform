#include "SensorViewCSharp.h"

void SensorViewCSharp::showDistanceInfo()
{
	for (size_t i = 0U; i < distanceSensors.size(); ++i)
	{
		if (distanceCallback)
		{
			distanceCallback(i, distanceSensors[i]);
		}
	}
}

void SensorViewCSharp::showLineInfo()
{
	for (size_t i = 0U; i < lineSensors.size(); ++i)
	{
		if (lineCallback)
		{
			lineCallback(i, lineSensors[i]);
		}
	}
}

void SensorViewCSharp::setLineCallback(sensor_callback callback)
{
	if (callback)
	{
		lineCallback = callback;
	}
}

void SensorViewCSharp::setDistanceCallback(sensor_callback callback)
{
	if (callback)
	{
		distanceCallback = callback;
	}
}
