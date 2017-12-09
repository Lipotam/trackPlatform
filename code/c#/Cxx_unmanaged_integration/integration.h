#pragma once
#include "GamepadManager.h"

#define DLL_EXPORT	__declspec( dllexport )

extern "C"
{
	DLL_EXPORT GamepadManager* connect(char* com_address, const unsigned long speed);
	DLL_EXPORT void disconnect(GamepadManager* manager);
}

