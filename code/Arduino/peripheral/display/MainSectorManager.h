/**
 * @(#) MainSectorManager.h
 */

#ifndef MAINSECTORMANAGER_H_H
#define MAINSECTORMANAGER_H_H

#include "Adafruit.h"
#include "StringDisplaySector.h"
#include "SectorInfoSaver.h"
#include "DisplayStateEnum.h"
#include "ToggleManager.h"

class MainSectorManager
{

public:
	MainSectorManager(Adafruit_GFX* gfx);
	void paint();
	void print_debug_string(const String info);

private:
	uint8_t current_combination;
	DisplayStateEnum current_state_;
	StringDisplaySector * display_sector_;
	SectorInfoSaver * states_;
	bool is_changed();

};

#endif
