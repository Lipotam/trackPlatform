/**
 * @(#) SectorInfoSaver.cpp
 */


#include "SectorInfoSaver.h"
bool SectorInfoSaver::is_changed()
{
	return false;
}

SectorInfoSaver::SectorInfoSaver(StringDisplaySector* sds) : is_changed_(true), display_sector_(sds)
{

}

void SectorInfoSaver::mark_changed()
{

}

