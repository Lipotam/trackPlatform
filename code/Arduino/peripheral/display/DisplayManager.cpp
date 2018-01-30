/**
 * @(#) DisplayManager.cpp
 */

#include "../../config/Constants.h"
#include "DisplayManager.h"
void DisplayManager::reset_all_connectors()
{
	connector_manager_.reset_all_connectors();
}

void DisplayManager::set_connector(const ConnectorEnum connector_index)
{
	connector_manager_.set_connector(connector_index);
}

void DisplayManager::set_processing_status(const ProcessingStatusEnum status)
{
	state_sector_.set_state(status);
}

DisplayManager::DisplayManager() : gfx_(),
								   connector_manager_(&gfx_),
								   line_sector_(&gfx_, Constants::kLineImageConfiguration),
								   state_sector_(&gfx_, Constants::kStatusImageConfiguration, Constants::kStatusImages, Constants::kStatusImagesNum),
								   main_view_manager_(&gfx_)
{
	gfx_.begin(SSD1306_SWITCHCAPVCC);
	gfx_.clearDisplay();
	//TODO: fix ssd1306 constructor
}

void DisplayManager::init_connector(const ConnectorEnum connector_index)
{
	connector_manager_.init_connector(connector_index);
}

void DisplayManager::print_debug_string(const String& info)
{
	main_view_manager_.print_debug_string(info);
}

void DisplayManager::repaint()
{
	connector_manager_.paint();
	line_sector_.paint();
	state_sector_.paint();
	main_view_manager_.paint();

	// refreshing real screen
	gfx_.display();
}

