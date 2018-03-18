/**
 * @(#) BasicDisplaySector.h
 */

#ifndef BASICDISPLAYSECTOR_H_H
#define BASICDISPLAYSECTOR_H_H

#include "Adafruit.h"
#include "../../config/ImageConfiguration.h"
class BasicDisplaySector
{

public:
	BasicDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration);
	bool is_changed() const;
	virtual void paint() = 0;

protected:
	ImageConfiguration config_;

	uint16_t default_back_color_;
	uint16_t default_main_color_;

	Adafruit_GFX* gfx_;

	bool is_changed_;

	void paint(const uint8_t* buffer, const uint16_t main_color, const uint16_t back_color);
};

#endif
