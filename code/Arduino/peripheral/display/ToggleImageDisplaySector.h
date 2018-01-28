/**
 * @(#) ToggleImageDisplaySector.h
 */

#ifndef TOGGLEIMAGEDISPLAYSECTOR_H_H
#define TOGGLEIMAGEDISPLAYSECTOR_H_H

#include "Adafruit.h"
#include "BasicDisplaySector.h"
#include "../../config/ImageConfiguration.h"
#include "ToggleStatesEnum.h"

class ToggleImageDisplaySector : public BasicDisplaySector
{

public:
	void set_state(const ToggleStatesEnum state);
	ToggleImageDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration, const uint8_t* released_buffer);

	void paint() override;

private:
	const uint8_t* released_image_;
	ToggleStatesEnum state_;
};

#endif
