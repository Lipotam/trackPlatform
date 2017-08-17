#ifndef _GAMEPAD_CONFIG_H_
#define _GAMEPAD_CONFIG_H_

enum class GamepadCommands
{
	none,

	/* App management */
	exit,

	/* Movement */
	moveRobotX,
	moveRobotY,
	moveCameraX,
	moveCameraY,
	
	/* Sensors */
	lineSensorRefresh,
	distanceSensorRefresh,
};

class GamepadConfig
{
	static const short int maxButtons = 14;
	static const short int maxSticks = 6;

	GamepadCommands buttonsBinding[maxButtons];
	GamepadCommands sticksBinding[maxSticks];
public:
	GamepadConfig();

	/**
	 * @return Button mapping command or @GamepadCommands::none, if not exists
	 */
	GamepadCommands button(int index) const;
	/**
	 * @return Button mapping command or @GamepadCommands::none, if not exists
	 */
	GamepadCommands stick(int index) const;
};

#endif /* _GAMEPAD_CONFIG_H_ */
