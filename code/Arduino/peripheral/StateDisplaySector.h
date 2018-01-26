#pragma once
#include "BasicDisplaySector.h"
#include "SectorStateEnum.h"

class StateDisplaySector : BasicDisplaySector
{
public:
	StateDisplaySector(const ImageConfiguration& configuration, Adafruit_GFX* binded_gfx);
	void use();
	void no_use();
	void clean();

protected:
	SectorStateEnum state_ = SectorStateEnum::clean;
};
