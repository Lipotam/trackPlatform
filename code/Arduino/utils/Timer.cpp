#include "Timer.h"

void Timer::updateState()
{
	if (state == timerState_started)
	{
		auto current_ms = millis();
		if (static_cast<uint32_t>(current_ms - startTime_ms) >= timeToSet_ms)
		{
			state = timerState_finished;
		}
	}
}

Timer::Timer(uint32_t timeToSet): startTime_ms(0), timeToSet_ms(timeToSet), passedTime_ms(0), state(timerState_stopped)
{
}

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
	switch (state)
	{
	case timerState_started:
	case timerState_paused: {
		state = timerState_stopped;
		break;
	}
	default: { break; }
	}
}

void Timer::reset()
{
	switch (state)
	{
	case timerState_started: {
		startTime_ms = millis();
		break;
	}
	case timerState_paused: {
		passedTime_ms = 0;
		break;
	}
	case timerState_finished: {
		state = timerState_stopped;
		break;
	}
	default: { break; }
	}
}

void Timer::pause()
{
	switch (state)
	{
	case timerState_started: {
		passedTime_ms = millis() - startTime_ms;
		state = timerState_paused;
		break;
	}
	default: { break; }
	}
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
