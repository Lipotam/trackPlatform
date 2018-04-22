#ifndef _GAMEPAD_CALLBACKS_H_
#define _GAMEPAD_CALLBACKS_H_

#include "gamepad/Gamepad.h"

/**
* @brief Checks changes of buttons
* @param context Pointer to @GamepadManager variable. Used to call events
*/
void onButtonDown(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
/**
 * @brief Checks is exit key was released
 * @param context Pointer to @GamepadManager variable. Sets to true, if exit key changed its pressing [pressed -> released], else sets false
 */
void onButtonUp(struct Gamepad_device * device, unsigned int buttonID, double timestamp, void * context);
/**
* @brief Checks changes of axes positions
* @param context Pointer to @GamepadManager variable. Used to call events
*/
void onAxisMoved(struct Gamepad_device * device, unsigned int axisID, float value, float lastValue, double timestamp, void * context);

#endif /* _GAMEPAD_CALLBACKS_H_ */
