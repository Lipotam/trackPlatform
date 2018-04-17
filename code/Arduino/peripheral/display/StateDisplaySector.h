/**
 * @(#) StateDisplaySector.h
 */

#ifndef STATEDISPLAYSECTOR_H_H
#define STATEDISPLAYSECTOR_H_H

#include "Adafruit.h"
#include "BasicDisplaySector.h"
#include "../../config/ImageConfiguration.h"

class StateDisplaySector : public BasicDisplaySector
{

public:
	void hide();
	void set_state(const uint8_t buffer_num);
	void show();
	StateDisplaySector(Adafruit_GFX* gfx, const ImageConfiguration configuration, const uint8_t* const* buffers, const uint8_t buffers_num);

	void paint() override;
private:
	const uint8_t*const* buffers_{nullptr};
	const uint8_t buffers_num_;
	uint8_t current_buffer_num_;

	bool is_visible_;
};

#endif
