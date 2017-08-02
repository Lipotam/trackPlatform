#include "Timer.h"

void Timer::updateState()
{
}

Timer::Timer(uint32_t timeToSet): startTime_ms(0), timeToSet_ms(timeToSet), passedTime_ms(0), state(timerState_stopped)
{
}

/*
 * switch(state)
	{
	case timerState_none: {
		break;
	}
	case timerState_started: {
		break;
	}
	case timerState_paused: {
		break;
	}
	case timerState_stopped: {
		break;
	}
	case timerState_finished: {
		break;
	}
	default: { break;}
	}
 */

void Timer::startOrResume()
{
	switch(state)
	{
	case timerState_paused: {
		startTime_ms = millis() - passedTime_ms;
		passedTime_ms = 0;
		state = timerState_started;
		break;
	}
	case timerState_stopped: {
		startTime_ms = millis();
		state = timerState_started;
		break;
	}
	default: { break; }
	}
}

void Timer::stop()
{
}

void Timer::reset()
{
}

void Timer::pause()
{
}

void Timer::setSetTime(uint32_t timeToSet)
{
	timeToSet_ms = timeToSet;
	updateState();
}

TimerState Timer::getState()
{
	updateState();
	return state;
}

bool Timer::isFinished()
{
	return (getState() == timerState_finished);
}
