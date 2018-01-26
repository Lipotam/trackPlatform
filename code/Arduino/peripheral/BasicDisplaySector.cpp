#include "../connection/DebugSerial.h"
#include "BasicDisplaySector.h"

BasicDisplaySector::BasicDisplaySector(const ImageConfiguration& configuration, Adafruit_GFX* binded_gfx): configuration_(configuration), view_(binded_gfx)
{
}

bool BasicDisplaySector::is_info_changed() const
{
	return is_info_changed_;
}

void BasicDisplaySector::paint()
{
	paint(configuration_.buffer, main_color_, background_color_);
}

void BasicDisplaySector::clear()
{
	paint(configuration_.buffer, background_color_, background_color_);
}

void BasicDisplaySector::paint(const uint8_t* buffer, const uint16_t main_color, const uint16_t background_color)
{
	if (!view_)
	{
		DEBUG_PRINTF("Adafruit_GFX is null. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	if (!buffer)
	{
		DEBUG_PRINTF("Image buffer is null. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	view_->drawBitmap(configuration_.x_pos, configuration_.y_pos, buffer, configuration_.x_size,
	                  configuration_.y_size, main_color, background_color);
}

