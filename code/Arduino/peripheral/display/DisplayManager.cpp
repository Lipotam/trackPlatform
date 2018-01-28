/**
 * @(#) DisplayManager.cpp
 */

#include "../../config/Constants.h"
#include "DisplayManager.h"
void DisplayManager::reset_all_connectors()
{
	//TODO
}

void DisplayManager::set_connector(const ConnectorEnum connector_index)
{
	//TODO
}

void DisplayManager::set_processing_status(const ProcessingStatusEnum status)
{
	//TODO
}

DisplayManager::DisplayManager() : gfx_(),
								   connector_manager_(&gfx_),
								   line_sector_(&gfx_, Constants::kLineImageConfiguration),
								   state_sector_(&gfx_, Constants::kStatusImageConfiguration, Constants::kStatusImages, Constants::kStatusImagesNum),
								   main_view_manager_(&gfx_)
{
	//TODO
}

void DisplayManager::init_connector(const ConnectorEnum connector_index)
{
	//TODO
}

void DisplayManager::print_debug_string(const String info)
{
	//TODO
}

void DisplayManager::repaint()
{
	//TODO
}

