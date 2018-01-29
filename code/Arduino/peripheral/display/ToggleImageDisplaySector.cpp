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
	if (!is_changed())
	{
		return;
	}

	uint16_t main_color;
	uint16_t back_color;
	switch (state_)
	{
	case pressed:
		main_color = default_back_color_;
		back_color = default_main_color_;
		break;
	case released:
		main_color = default_main_color_;
		back_color = default_back_color_;
		break;
	case hidden:
	default:
		main_color = default_back_color_;
		back_color = default_back_color_;
		break;
	}

	BasicDisplaySector::paint(released_image_, main_color, back_color);
	is_changed_ = false;
}
