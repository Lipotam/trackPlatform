#include "StateDisplaySector.h"

StateDisplaySector::StateDisplaySector(const ImageConfiguration& configuration, Adafruit_GFX* binded_gfx)
	: BasicDisplaySector(configuration, binded_gfx)
{
}

void StateDisplaySector::use()
{
	if (state_ != SectorStateEnum::using_now)
	{
		is_info_changed_ = true;
		paint(configuration_.buffer, background_color_, main_color_);
	}
}

void StateDisplaySector::no_use()
{
	if (state_ != SectorStateEnum::not_using_now)
	{
		is_info_changed_ = true;
		paint(configuration_.buffer, main_color_, background_color_);
	}
}

void StateDisplaySector::clean()
{
	if (state_ != SectorStateEnum::clean)
	{
		is_info_changed_ = true;
		clean();
	}
}
