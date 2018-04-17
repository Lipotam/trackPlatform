/**
 * @(#) BasicDisplaySector.cpp
 */

#include "../../connection/DebugSerial.h"
#include "BasicDisplaySector.h"

BasicDisplaySector::BasicDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration) :
	config_(configuration), default_back_color_(BLACK), default_main_color_(WHITE), gfx_(gfx), is_changed_(true)
{

}

void BasicDisplaySector::paint(const uint8_t* buffer, const uint16_t main_color, const uint16_t back_color)
{
	if (!gfx_)
	{
		DEBUG_PRINTF("Adafruit GFX module is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	if (!buffer)
	{
		DEBUG_PRINTF("Print buffer is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	gfx_->drawBitmap(config_.x_pos, config_.y_pos, buffer, config_.x_size, config_.y_size, main_color, back_color);
}

bool BasicDisplaySector::is_changed() const
{
	return is_changed_;
}

