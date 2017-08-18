#include "GamepadConfig.h"

GamepadConfig::GamepadConfig() : 
	buttonsBinding {
		GamepadCommands::none,                         /* 0 */
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
	}, 
	sticksBinding {
		GamepadCommands::moveRobotX,                   /* 0 - left X */
		GamepadCommands::moveRobotY,                   /* 1 - left Y */
		GamepadCommands::moveCameraX,                  /* 2 - right X */
		GamepadCommands::moveCameraY,                  /* 3 - right Y */
		GamepadCommands::none,                         /* 4 */
		GamepadCommands::none,                         /* 5 */
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

int GamepadConfig::getStickId(GamepadCommands command) const
{
	for (auto i = 0; i < maxButtons; ++i)
	{
		if (buttonsBinding[i] == command)
		{
			return i;
		}
	}

	return badIndex;
}
