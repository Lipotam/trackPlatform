/**
 * @(#) WiFiDisplaySectorManager.cpp
 */

#include "../../connection/DebugSerial.h"
#include "../../config/Constants.h"
#include "WiFiSectorInfoSaver.h"

WiFiSectorInfoSaver::WiFiSectorInfoSaver(StringDisplaySector* sds) : 
	SectorInfoSaver(sds),
	info_prefix_(" "),
	ap_ip_row_info_("Server IP: "),
	ap_name_row_info_("AP: "),
	ap_password_row_info_("Password: "),
	ap_ip_row_(info_prefix_ + Constants::kWifiIp),
	ap_name_row_(info_prefix_ + Constants::kWifiAp),
	ap_password_row_(info_prefix_ + Constants::kWifiPassword)
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
	display_sector_->set_row(ap_name_row_info_, kApNameRowInfo);
	display_sector_->set_row(ap_password_row_info_, kApPasswordRowInfo);
	display_sector_->set_row(ap_ip_row_info_, kApIpRowInfo);
	display_sector_->set_row(ap_name_row_, kApNameRowNum);
	display_sector_->set_row(ap_password_row_, kApPasswordRowNum);
	display_sector_->set_row(ap_ip_row_, kApIpRowNum);

	is_changed_ = false;
}

