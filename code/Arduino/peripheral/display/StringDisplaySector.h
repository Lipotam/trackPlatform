/**
 * @(#) StringDisplaySector.h
 */

#ifndef STRINGDISPLAYSECTOR_H_H
#define STRINGDISPLAYSECTOR_H_H

#include "Adafruit.h"
#include "BasicDisplaySector.h"
#include "../../config/ImageConfiguration.h"

class StringDisplaySector : BasicDisplaySector
{

public:
	void set_header(const String s);
	void set_row(const String s, const uint8_t i);
	StringDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration configuration, const uint8_t header_font_size, const uint8_t main_font_size);

private:
	String header_;
	String shift_buffer_;
};

#endif
