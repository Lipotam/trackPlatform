#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../config/ImageConfiguration.h"

class BasicDisplaySector
{
public:
	BasicDisplaySector(ImageConfiguration configuration, Adafruit_GFX* binded_gfx);
	virtual ~BasicDisplaySector() = default;

	bool is_info_changed() const;

	virtual void paint();
	void clear();

protected:
	bool info_changed_ = true;
	const ImageConfiguration configuration_;
	Adafruit_GFX* view_;
	const uint16_t main_color_ = WHITE;
	const uint16_t background_color_ = BLACK;

	void paint(uint16_t main_color, uint16_t background_color);
};
