/**
 * @(#) BluetoothSectorInfoSaver.h
 */

#ifndef BLUETOOTHDISPLAYSECTORMANAGER_H_H
#define BLUETOOTHDISPLAYSECTORMANAGER_H_H

#include "SectorInfoSaver.h"
#include "StringDisplaySector.h"
class BluetoothSectorInfoSaver : public SectorInfoSaver
{

public:
	BluetoothSectorInfoSaver(StringDisplaySector* sds);
	void paint() override;

private:
	String info_prefix_;

	String ap_name_row_info_;
	String ap_password_row_info_;
	String ap_name_row_;
	String ap_password_row_;

	static const uint8_t kApNameRowNumInfo = 0;
	static const uint8_t kApPasswordRowNumInfo = 2;
	static const uint8_t kApNameRowNum = 1;
	static const uint8_t kApPasswordRowNum = 3;
};

#endif
