/**
 * @(#) ToggleManager.h
 */

#ifndef TOGGLEMANAGER_H_H
#define TOGGLEMANAGER_H_H

#include <stdint.h>

class ToggleManager
{
public:
	ToggleManager(const uint8_t* pins, const uint8_t pin_amount);

	uint8_t get_combination() const;

private:
	const uint8_t* pins_;
	const uint8_t pin_amount_;
};

#endif
