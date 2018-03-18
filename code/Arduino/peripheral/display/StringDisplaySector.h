/**
 * @(#) StringDisplaySector.h
 */

#ifndef STRINGDISPLAYSECTOR_H_H
#define STRINGDISPLAYSECTOR_H_H

#include "Adafruit.h"
#include "BasicDisplaySector.h"
#include "../../config/ImageConfiguration.h"

class StringDisplaySector : public BasicDisplaySector
{

public:
	static const uint8_t kRowAmount = 6;

	void set_header(const String& s);
	void set_row(const String& s, const uint8_t i);
	void clear();
	StringDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration, const uint8_t header_font_size, const uint8_t main_font_size);

	void paint() override;

private:
	static const uint8_t kTextColor = WHITE;

	String header_;
	String rows_[kRowAmount];

	const uint8_t header_font_size_;
	const uint8_t main_font_size_;

	void print_one_row(const String& s);
};

#endif
