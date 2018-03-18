/**
 * @(#) SectorInfoSaver.cpp
 */


#include "SectorInfoSaver.h"
bool SectorInfoSaver::is_changed()
{
	return is_changed_;
}

SectorInfoSaver::SectorInfoSaver(StringDisplaySector* sds) : display_sector_(sds), is_changed_(true)
{

}

void SectorInfoSaver::mark_changed()
{
	is_changed_ = true;
}

