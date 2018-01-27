/**
 * @(#) WiFiSectorInfoSaver.h
 */

#ifndef WIFIDISPLAYSECTORMANAGER_H_H
#define WIFIDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"

class WiFiSectorInfoSaver : SectorInfoSaver
{

public:
	WiFiSectorInfoSaver(StringDisplaySector* sds);

private:
	String ap_ip_;
	String ap_name_;
	String ap_password_;
};

#endif
