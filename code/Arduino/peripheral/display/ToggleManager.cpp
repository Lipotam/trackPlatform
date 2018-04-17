/**
 * @(#) ToggleManager.cpp
 */

#include <Arduino.h>
#include "ToggleManager.h"

ToggleManager::ToggleManager(const uint8_t* pins, const uint8_t pin_amount) :
	pins_(pins),
	pin_amount_(pin_amount)
{
	for(uint8_t i = 0; i < pin_amount_; ++i)
	{
		pinMode(pins_[i], INPUT_PULLUP);
	}
}

uint8_t ToggleManager::get_combination() const
{
	uint8_t answer = 0;

	for(uint8_t i = 0; i < pin_amount_; ++i)
	{
		answer <<= 1;
		const bool is_high = (digitalRead(pins_[i]) == HIGH);
		answer += (is_high ? 1 : 0);
	}

	return answer;
}

