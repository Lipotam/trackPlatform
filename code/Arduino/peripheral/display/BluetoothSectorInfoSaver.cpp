/**
 * @(#) BluetoothDisplaySectorManager.cpp
 */

#include "../../config/Constants.h"
#include "BluetoothSectorInfoSaver.h"
BluetoothSectorInfoSaver::BluetoothSectorInfoSaver(StringDisplaySector* sds) : SectorInfoSaver(sds),
                                                                               ap_name_(Constants::kBluetoothAp),
                                                                               ap_password_(
	                                                                               Constants::kBluetoothPassword)
{

}

