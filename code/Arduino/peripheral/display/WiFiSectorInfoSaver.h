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
	String info_prefix_;

	String ap_ip_row_info_;
	String ap_name_row_info_;
	String ap_password_row_info_;
	String ap_ip_row_;
	String ap_name_row_;
	String ap_password_row_;

	static const uint8_t kApNameRowInfo = 0;
	static const uint8_t kApPasswordRowInfo = 2;
	static const uint8_t kApIpRowInfo = 4;
	static const uint8_t kApNameRowNum = 1;
	static const uint8_t kApPasswordRowNum = 3;
	static const uint8_t kApIpRowNum = 5;
};

#endif
