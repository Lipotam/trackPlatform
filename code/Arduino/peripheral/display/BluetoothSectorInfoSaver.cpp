/**
 * @(#) BluetoothDisplaySectorManager.cpp
 */

#include "../../connection/DebugSerial.h"
#include "../../config/Constants.h"
#include "BluetoothSectorInfoSaver.h"
BluetoothSectorInfoSaver::BluetoothSectorInfoSaver(StringDisplaySector* sds) :
	SectorInfoSaver(sds), 
	info_prefix_(" "),
	ap_name_row_info_("AP: "), 
	ap_password_row_info_("Password: "),
	ap_name_row_(info_prefix_ + Constants::kBluetoothAp), 
	ap_password_row_(info_prefix_ + Constants::kBluetoothPassword)
{
	header_ = Constants::kBluetoothHeader;
}

void BluetoothSectorInfoSaver::paint()
{
	if (!display_sector_)
	{
		DEBUG_PRINTF("Display sector module is not initialized. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}
	display_sector_->clear();
	display_sector_->set_header(header_);
	display_sector_->set_row(ap_name_row_info_, kApNameRowNumInfo);
	display_sector_->set_row(ap_password_row_info_, kApPasswordRowNumInfo);
	display_sector_->set_row(ap_name_row_, kApNameRowNum);
	display_sector_->set_row(ap_password_row_, kApPasswordRowNum);

	is_changed_ = false;
}

