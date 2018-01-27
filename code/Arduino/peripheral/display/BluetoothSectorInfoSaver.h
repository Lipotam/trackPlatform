/**
 * @(#) BluetoothSectorInfoSaver.h
 */

#ifndef BLUETOOTHDISPLAYSECTORMANAGER_H_H
#define BLUETOOTHDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"
class BluetoothSectorInfoSaver : SectorInfoSaver
{

public:
	BluetoothSectorInfoSaver(StringDisplaySector* sds);

private:
	String ap_name_;
	String ap_password_;
};

#endif
