/**
 * @(#) StringDisplaySector.cpp
 */


#include "StringDisplaySector.h"
StringDisplaySector::StringDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration, const uint8_t header_font_size, const uint8_t main_font_size) :
	BasicDisplaySector(gfx, configuration),
	header_font_size_(header_font_size),
	main_font_size_(main_font_size)
{

}

void StringDisplaySector::paint()
{
	//TODO
	is_changed_ = false;
}

void StringDisplaySector::set_header(const String& s)
{
	if (header_ != s)
	{
		header_ = s;
		is_changed_ = true;
	}
}

void StringDisplaySector::set_row(const String& s, const uint8_t i)
{
	if (i < kRowAmount && rows_[i] != s)
	{
		rows_[i] = s;
		is_changed_ = true;
	}
}

void StringDisplaySector::clear()
{
	set_header("");
	for (uint8_t i = 0; i < kRowAmount; ++i)
	{
		set_row("", i);
	}
}

