/**
 * @(#) DebugSectorInfoSaver.h
 */

#ifndef DEBUGDISPLAYSECTORMANAGER_H_H
#define DEBUGDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"
class DebugSectorInfoSaver : SectorInfoSaver
{

public:
	DebugSectorInfoSaver(StringDisplaySector* sds);

};

#endif
