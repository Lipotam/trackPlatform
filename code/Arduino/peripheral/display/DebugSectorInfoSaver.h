/**
 * @(#) DebugSectorInfoSaver.h
 */

#ifndef DEBUGDISPLAYSECTORMANAGER_H_H
#define DEBUGDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"
class DebugSectorInfoSaver : public SectorInfoSaver
{

public:
	DebugSectorInfoSaver(StringDisplaySector* sds);

	void paint() override;
	void print_debug_string(const String& info);

protected:
	static const uint8_t kBufferRowAmount = StringDisplaySector::kRowAmount;
	
	String buffer_[kBufferRowAmount];
	uint8_t buffer_write_pos_ = 0;
};

#endif
