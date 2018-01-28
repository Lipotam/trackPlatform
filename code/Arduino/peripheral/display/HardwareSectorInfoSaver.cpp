/**
 * @(#) HardwareSectorInfoSaver.cpp
 */

#include "../../config/Constants.h"
#include "../../connection/DebugSerial.h"
#include "../../management/CommandManager.h"
#include "HardwareSectorInfoSaver.h"
HardwareSectorInfoSaver::HardwareSectorInfoSaver(StringDisplaySector* sds) : 
	SectorInfoSaver(sds), 
	compilation_date_time_(__TIMESTAMP__),
	min_supported_api_("Min supported API: " + String(CommandManager::min_api)),
	max_supported_api_("Max supported API: " + String(CommandManager::max_api))
{
	header_ = Constants::kHardwareInfoHeader;
}

void HardwareSectorInfoSaver::paint()
{
	if (!display_sector_)
	{
		DEBUG_PRINTF("Display sector module is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	display_sector_->clear();
	display_sector_->set_header(header_);
	display_sector_->set_row("Firmware was compiled on", kCompilationDateTimeMessageIndex);
	display_sector_->set_row(compilation_date_time_, kCompilationDateTimeIndex);
	display_sector_->set_row(min_supported_api_, kSupportedMinApiIndex);
	display_sector_->set_row(max_supported_api_, kSupportedMaxApiIndex);
}

