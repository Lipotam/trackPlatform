/**
 * @(#) WiFiSectorInfoSaver.h
 */

#ifndef WIFIDISPLAYSECTORMANAGER_H_H
#define WIFIDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"

class WiFiSectorInfoSaver : public SectorInfoSaver
{

public:
	WiFiSectorInfoSaver(StringDisplaySector* sds);
	void paint() override;

private:
	String ap_ip_row_;
	String ap_name_row_;
	String ap_password_row_;

	static const uint8_t kApNameRowNum = 0;
	static const uint8_t kApPasswordRowNum = 1;
	static const uint8_t kApIpRowNum = 2;
};

#endif
