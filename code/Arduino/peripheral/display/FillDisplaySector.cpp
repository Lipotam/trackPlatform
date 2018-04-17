/**
 * @(#) FillDisplaySector.cpp
 */


#include "FillDisplaySector.h"

FillDisplaySector::FillDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration) :
	BasicDisplaySector(gfx, configuration)
{
}

void FillDisplaySector::paint()
{
	if (is_changed())
	{
		gfx_->fillRect(config_.x_pos, config_.y_pos, config_.x_size, config_.y_size, default_main_color_);
		is_changed_ = false;
	}
}
