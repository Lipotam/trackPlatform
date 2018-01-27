/**
 * @(#) SectorInfoSaver.h
 */

#ifndef SECTORINFOSAVER_H_H
#define SECTORINFOSAVER_H_H

#include "StringDisplaySector.h"
class SectorInfoSaver
{

public:
	bool is_changed();
	void mark_changed();
	virtual void paint() = 0;
	SectorInfoSaver(StringDisplaySector* sds);

private:
	StringDisplaySector* display_sector_;
	String header_;

	bool is_changed_;
};

#endif
