/**
 * @(#) SectorInfoSaver.cpp
 */


#include "SectorInfoSaver.h"
bool SectorInfoSaver::is_changed()
{
	return false;
}

SectorInfoSaver::SectorInfoSaver(StringDisplaySector* sds) : display_sector_(sds), is_changed_(true)
{

}

void SectorInfoSaver::mark_changed()
{

}

