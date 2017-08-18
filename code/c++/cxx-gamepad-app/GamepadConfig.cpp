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
		GamepadCommands::distanceSensorRefresh,        /* 10 - 3 on defender */
		GamepadCommands::lineSensorRefresh,            /* 11 - 2 on defender */
		GamepadCommands::exit,                         /* 12 - 4 on defender */
		GamepadCommands::none,                         /* 13 - 1 on defender */
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
