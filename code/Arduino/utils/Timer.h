#pragma once

#include <Arduino.h>

enum TimerState {
	timerState_none,
	timerState_started,
	timerState_paused,
	timerState_stopped,
	timerState_finished
};

class Timer
{
	uint32_t startTime_ms;
	uint32_t timeToSet_ms;
	uint32_t passedTime_ms;							//used only to pause timer
	TimerState state;

protected:
	/**
	 * @brief Updates current state information
	 */
	void update_state();

public:
	/**
	 * @brief Creates timer and sets
	 *
	 * @param timeToSet Time to set timer in milliseconds
	 */
	Timer(uint32_t timeToSet);

	/**
	 * @brief Starts or resumes setting timer
	 */
	void start_or_resume();
	/**
	 * @brief Stop setting timer and resets time to beginning value
	 * @warning Cannot stop finished timer (it will not change state)
	 */
	void stop();
	/**
	 * @brief Resets timer (resets time to require to set timer to beginnig value, but not pause/stop it)
	 * @warning If timer was finished before, it will be in stopped state
	 */
	void reset();
	/**
	 * @brief Pause setting timer
	 */
	void pause();
	/**
	 * @brief Sets time to set to timer, but not reset timer (reset it manual, if require)
	 *
	 * @param timeToSet New time to set timer in milliseconds
	 */
	void setSetTime(uint32_t timeToSet);
	/**
	 * @brief Checks timeout and gets timer state
	 * @return State of timer
	 */
	TimerState getState();
	/**
	 * @brief Checks timeout and gets is timer setted
	 * @return true, if timer setted/finished (time were passed), else false
	 */
	bool isFinished();
};
