/**
 * @(#) DisplayManager.cpp
 */

#include "../../config/Constants.h"
#include "DisplayManager.h"


#if (SSD1306_LCDWIDTH != 128)
#error("Width incorrect (not 128), please fix Adafruit_SSD1306.h!");
#endif
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect (not 64), please fix Adafruit_SSD1306.h!");
#endif

DisplayManager* DisplayManager::manager_ = nullptr;

void DisplayManager::reset_all_connectors()
{
	connector_manager_.reset_all_connectors();
	state_sector_.hide();
}

void DisplayManager::set_connector(const ConnectorEnum connector_index)
{
	connector_manager_.set_connector(connector_index);
	state_sector_.show();
}

void DisplayManager::set_processing_status(const ProcessingStatusEnum status)
{
	state_sector_.set_state(status);
}

DisplayManager* DisplayManager::get_manager()
{
	if (!manager_)
	{
		manager_ = new DisplayManager();
	}

	return manager_;
}

DisplayManager::DisplayManager() : gfx_(Constants::kDisplayDcPin, Constants::kDisplayResetPin, Constants::kDisplayCsPin),
								   connector_manager_(&gfx_),
								   line_sector_(&gfx_, Constants::kLineImageConfiguration),
								   state_sector_(&gfx_, Constants::kStatusImageConfiguration, Constants::kStatusImages, Constants::kStatusImagesNum),
								   main_view_manager_(&gfx_)
{
	gfx_.begin(SSD1306_SWITCHCAPVCC);
	gfx_.clearDisplay();
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

