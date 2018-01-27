/**
 * @(#) DisplayManager.h
 */

#ifndef DISPLAYMANAGER_H_H
#define DISPLAYMANAGER_H_H

#include "MainSectorManager.h"
#include "FillDisplaySector.h"
#include "ConnectionSectorManager.h"
#include "ProcessingStatusEnum.h"

class DisplayManager
{

public:
	void init_connector(const ConnectorEnum connector_index);
	void print_debug_string(const String info);
	void repaint();
	void reset_all_connectors();
	void set_connector(const ConnectorEnum connector_index);
	void set_processing_status(const ProcessingStatusEnum status);

private:
	ConnectionSectorManager connector_manager_;
	FillDisplaySector line_sector_;
	MainSectorManager main_view_manager_;
};

#endif
