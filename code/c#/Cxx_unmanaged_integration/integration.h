#pragma once
#include "GamepadManager.h"

#define DLL_EXPORT	__declspec( dllexport )

extern "C"
{
	typedef void(*sensor_callback)(int sensorIndex, unsigned long value);

	DLL_EXPORT GamepadManager* connect(char* com_address, const unsigned long speed);
	DLL_EXPORT void disconnect(GamepadManager* manager);
	DLL_EXPORT void set_sensor_callbacks(sensor_callback distanceSensorCallback, sensor_callback lineSensorCallback);
}

