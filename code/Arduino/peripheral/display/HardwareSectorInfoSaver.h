/**
 * @(#) HardwareSectorInfoSaver.h
 */

#ifndef HARDWARESECTORINFOSAVER_H_H
#define HARDWARESECTORINFOSAVER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"
class HardwareSectorInfoSaver : public SectorInfoSaver
{

public:
	HardwareSectorInfoSaver(StringDisplaySector* sds);
	void paint() override;

private:
	static const uint8_t kCompilationDateTimeMessageIndex = 0;
	static const uint8_t kCompilationDateTimeIndex = 1;
	static const uint8_t kSupportedMinApiIndex = 2;
	static const uint8_t kSupportedMaxApiIndex = 3;

	const String compilation_date_time_;
	const String min_supported_api_;
	const String max_supported_api_;
};

#endif
