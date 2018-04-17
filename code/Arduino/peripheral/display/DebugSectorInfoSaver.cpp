/**
 * @(#) DebugDisplaySectorManager.cpp
 */

#include "../../connection/DebugSerial.h"
#include "../../config/Constants.h"
#include "DebugSectorInfoSaver.h"
DebugSectorInfoSaver::DebugSectorInfoSaver(StringDisplaySector* sds): SectorInfoSaver(sds)
{
	header_ = Constants::kDebugHeader;
}

void DebugSectorInfoSaver::paint()
{
	if (!display_sector_)
	{
		DEBUG_PRINTF("Display sector module is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	display_sector_->clear();
	display_sector_->set_header(header_);
	for (uint8_t i = 0; i < kBufferRowAmount; ++i)
	{
		display_sector_->set_row(buffer_[(i + buffer_write_pos_) % kBufferRowAmount], i);
	}
	is_changed_ = false;
}

void DebugSectorInfoSaver::print_debug_string(const String& info)
{
	buffer_[buffer_write_pos_] = info;
	buffer_write_pos_++;
	is_changed_ = true;
}
