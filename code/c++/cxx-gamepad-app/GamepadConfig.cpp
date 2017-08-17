#include "GamepadConfig.h"

GamepadConfig::GamepadConfig() : 
	buttonsBinding {
		GamepadCommands::distanceSensorRefresh,        /* 1 - A */
		GamepadCommands::exit,                         /* 2 - B */
		GamepadCommands::lineSensorRefresh,            /* 3 - X */
		GamepadCommands::none,                         /* 4 - Y */
		GamepadCommands::none,                         /* 5 */
		GamepadCommands::none,                         /* 6 */
		GamepadCommands::none,                         /* 7 */
		GamepadCommands::none,                         /* 8 */
		GamepadCommands::none,                         /* 9 */
		GamepadCommands::none,                         /* 10 */
		GamepadCommands::none,                         /* 11 */
		GamepadCommands::none,                         /* 12 */
		GamepadCommands::none,                         /* 13 */
		GamepadCommands::none,                         /* 14 */
	}, 
	sticksBinding {
		GamepadCommands::moveRobotX,                   /* 1 - left X */
		GamepadCommands::moveRobotY,                   /* 2 - left Y */
		GamepadCommands::moveCameraX,                  /* 3 - right X */
		GamepadCommands::moveCameraY,                  /* 4 - right Y */
		GamepadCommands::none,                         /* 5 */
		GamepadCommands::none,                         /* 6 */
	}
{
}

GamepadCommands GamepadConfig::button(int index) const
{
    return ((index >= 0) && (index < maxButtons)) ? buttonsBinding[index] : GamepadCommands::none;
}

GamepadCommands GamepadConfig::stick(int index) const
{
    return ((index >= 0) && (index < maxSticks)) ? sticksBinding[index] : GamepadCommands::none;
}
