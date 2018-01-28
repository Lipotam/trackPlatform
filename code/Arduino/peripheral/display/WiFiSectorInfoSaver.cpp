/**
 * @(#) WiFiDisplaySectorManager.cpp
 */

#include "../../connection/DebugSerial.h"
#include "../../config/Constants.h"
#include "WiFiSectorInfoSaver.h"

WiFiSectorInfoSaver::WiFiSectorInfoSaver(StringDisplaySector* sds) : 
	SectorInfoSaver(sds),
	ap_ip_row_("Server IP: " + Constants::kWifiIp),
	ap_name_row_("AP: " + Constants::kWifiAp),
	ap_password_row_("Password: " + Constants::kWifiPassword)
{
	header_ = Constants::kWifiHeader;
}

void WiFiSectorInfoSaver::paint()
{
	if (!display_sector_)
	{
		DEBUG_PRINTF("Display sector module is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	display_sector_->clear();
	display_sector_->set_header(header_);
	display_sector_->set_row(ap_name_row_, kApNameRowNum);
	display_sector_->set_row(ap_password_row_, kApPasswordRowNum);
	display_sector_->set_row(ap_ip_row_, kApIpRowNum);

	is_changed_ = false;
}

