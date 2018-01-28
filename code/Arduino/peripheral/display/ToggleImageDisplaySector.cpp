/**
 * @(#) ToggleImageDisplaySector.cpp
 */


#include "ToggleImageDisplaySector.h"
void ToggleImageDisplaySector::set_state(const ToggleStatesEnum state)
{
	if (state_ != state)
	{
		state_ = state;
		is_changed_ = true;
	}
}

ToggleImageDisplaySector::ToggleImageDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration,
                                                   const uint8_t* released_buffer) : 
	BasicDisplaySector(gfx, configuration),
	released_image_(released_buffer), 
	state_(hidden)
{

}

void ToggleImageDisplaySector::paint()
{
	//TODO
}

