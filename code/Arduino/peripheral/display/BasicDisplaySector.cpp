/**
 * @(#) BasicDisplaySector.cpp
 */


#include "BasicDisplaySector.h"

BasicDisplaySector::BasicDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration) :
	config_(configuration), default_back_color_(BLACK), default_main_color_(WHITE), gfx_(gfx), is_changed_(true)
{

}

void BasicDisplaySector::paint(const uint8_t* buffer, const uint16_t main_color, const uint16_t back_color)
{

}

bool BasicDisplaySector::is_changed()
{
	return false;
}

