/**
 * @(#) ToggleImageDisplaySector.cpp
 */


#include "ToggleImageDisplaySector.h"
void ToggleImageDisplaySector::set_state(const ToggleStatesEnum state)
{

}

ToggleImageDisplaySector::ToggleImageDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration, const uint8_t* released_buffer) : 
	BasicDisplaySector(gfx, configuration),
	state_(hidden), released_image_(released_buffer)
{

}

void ToggleImageDisplaySector::paint()
{
}

