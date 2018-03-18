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
	static const uint8_t kCompilationDateIndex = 1;
	static const uint8_t kCompilationTimeIndex = 2;
	static const uint8_t kSupportedMinApiIndex = 4;
	static const uint8_t kSupportedMaxApiIndex = 5;

	const String compilation_date_time_prefix_;
	const String compilation_date_;
	const String compilation_time_;
	const String min_supported_api_;
	const String max_supported_api_;
};

#endif
