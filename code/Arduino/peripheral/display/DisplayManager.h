/**
 * @(#) DisplayManager.h
 */

#ifndef DISPLAYMANAGER_H_H
#define DISPLAYMANAGER_H_H

#include "Adafruit.h"
#include "MainSectorManager.h"
#include "FillDisplaySector.h"
#include "ConnectionSectorManager.h"
#include "ProcessingStatusEnum.h"
#include "StateDisplaySector.h"

class DisplayManager
{

public:
	void init_connector(const ConnectorEnum connector_index);
	void print_debug_string(const String& info);
	void repaint();
	void reset_all_connectors();
	void set_connector(const ConnectorEnum connector_index);
	void set_processing_status(const ProcessingStatusEnum status);

	static DisplayManager* get_manager();

private:
	Adafruit_SSD1306 gfx_;
	ConnectionSectorManager connector_manager_;
	FillDisplaySector line_sector_;
	StateDisplaySector state_sector_;
	MainSectorManager main_view_manager_;

	static DisplayManager* manager_;
	DisplayManager();
	DisplayManager(DisplayManager&) = default;
	~DisplayManager() = default;
};

#endif
