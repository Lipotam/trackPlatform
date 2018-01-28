/**
 * @(#) FillDisplaySector.cpp
 */


#include "FillDisplaySector.h"

void FillDisplaySector::paint()
{
	gfx_->drawRect(config_.x_pos, config_.y_pos, config_.x_size, config_.y_size, default_main_color_);
	is_changed_ = false;
}
