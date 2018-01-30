/**
 * @(#) MainSectorManager.h
 */

#ifndef MAINSECTORMANAGER_H_H
#define MAINSECTORMANAGER_H_H

#include "Adafruit.h"
#include "SectorInfoSaver.h"
#include "ToggleManager.h"
#include "DebugSectorInfoSaver.h"

class MainSectorManager
{

public:
	MainSectorManager(Adafruit_GFX* gfx);
	void paint();
	void print_debug_string(const String& info);

private:
	static const uint8_t kHeaderFontSize = 2;
	static const uint8_t kMainFontSize = 1;
	static const uint8_t kDisplayStates = 4;

	uint8_t current_combination_;
	SectorInfoSaver* states_[kDisplayStates]{ nullptr };

	DebugSectorInfoSaver* debug_info_saver_;
	ToggleManager toggle_manager_;
	StringDisplaySector sds_;
};

#endif
