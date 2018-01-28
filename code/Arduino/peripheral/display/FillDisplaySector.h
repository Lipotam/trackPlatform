/**
 * @(#) FillDisplaySector.h
 */

#ifndef FILLDISPLAYSECTOR_H_H
#define FILLDISPLAYSECTOR_H_H

#include "BasicDisplaySector.h"
class FillDisplaySector : public BasicDisplaySector
{
public:
	FillDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration& configuration);
	void paint() override;
};

#endif
