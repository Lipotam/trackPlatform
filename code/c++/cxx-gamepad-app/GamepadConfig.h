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

	/**
	 * Convert command to stick id that binds with that command
	 * @return Binding key index or @badIndex, if not exists
	 */
	int getStickId(GamepadCommands command) const;

	static const int badIndex = -1;
};

#endif /* _GAMEPAD_CONFIG_H_ */
