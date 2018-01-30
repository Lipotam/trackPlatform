/**
 * @(#) StateDisplaySector.cpp
 */

#include "../../connection/DebugSerial.h"
#include "StateDisplaySector.h"

StateDisplaySector::StateDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration configuration, const uint8_t* const* buffers, const uint8_t buffers_num) : 
	BasicDisplaySector(gfx, configuration), 
	buffers_(buffers),
	buffers_num_(buffers_num),
	current_buffer_num_(0),
	is_visible_(false)
{
}

void StateDisplaySector::paint()
{
	if (current_buffer_num_ > buffers_num_)
	{
		DEBUG_PRINTF("Index out of range. Func: %s, line: %d\n", __FUNCTION__, __LINE__);
		return;
	}

	if(is_changed())
	{
		BasicDisplaySector::paint(
			buffers_[current_buffer_num_], 
			is_visible_ ? default_main_color_ : default_back_color_,
		    default_back_color_);
	}
}

void StateDisplaySector::hide()
{
	if (is_visible_ != false)
	{
		is_visible_ = false;
		is_changed_ = true;
	}
}

void StateDisplaySector::show()
{
	if (is_visible_ != true)
	{
		is_visible_ = true;
		is_changed_ = true;
	}
}

void StateDisplaySector::set_state(const uint8_t buffer_num)
{
	if (current_buffer_num_ != buffer_num)
	{
		current_buffer_num_ = buffer_num;
		is_changed_ = true;
	}
}

