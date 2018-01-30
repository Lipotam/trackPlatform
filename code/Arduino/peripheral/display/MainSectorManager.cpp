/**
 * @(#) MainSectorManager.cpp
 */

#include "../../config/Constants.h"
#include "BluetoothSectorInfoSaver.h"
#include "WiFiSectorInfoSaver.h"
#include "HardwareSectorInfoSaver.h"
#include "StringDisplaySector.h"
#include "DisplayStateEnum.h"

#include "MainSectorManager.h"

void MainSectorManager::print_debug_string(const String& info)
{
	debug_info_saver_->print_debug_string(info);
}

void MainSectorManager::paint()
{
	const uint8_t new_combination = toggle_manager_.get_combination();
	if (new_combination != current_combination_)
	{
		states_[current_combination_]->mark_changed();
		current_combination_ = new_combination;
	}

	SectorInfoSaver* current_state = states_[current_combination_];
	if (current_state->is_changed())
	{
		current_state->paint();
	}

	sds_.paint();
}

MainSectorManager::MainSectorManager(Adafruit_GFX* gfx) :
	current_combination_(0),
	toggle_manager_(Constants::kDisplayTogglePins, Constants::kDisplayTogglePinAmount),
	sds_(gfx, Constants::kPrintAreaImageConfiguration, kHeaderFontSize, kMainFontSize)
{
	debug_info_saver_ = new DebugSectorInfoSaver(&sds_);
	states_[DisplayStateEnum::bluetooth_display_state] = new BluetoothSectorInfoSaver(&sds_);
	states_[DisplayStateEnum::wi_fi_display_state] = new WiFiSectorInfoSaver(&sds_);
	states_[DisplayStateEnum::hardware_display_state] = new HardwareSectorInfoSaver(&sds_);
	states_[DisplayStateEnum::debug_display_state] = debug_info_saver_;
}
