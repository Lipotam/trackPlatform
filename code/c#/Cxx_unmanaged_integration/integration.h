#pragma once
#include "TrackPlatform_Manager.h"

#define DllExport   __declspec( dllexport )

extern "C"
{
	DllExport void SayHello()
	{
		try
		{
			TrackPlatform_Manager manager(bluetooth, CommunicationInfoStruct());
		}
		catch (...)
		{
		}
	}
}

