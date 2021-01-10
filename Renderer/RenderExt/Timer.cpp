#include "Timer.h"

Timer::Timer()
{
}

bool Timer::Tick()
{
	mCurrentTime = this->Now();
	if (mCurrentTime - mLastTime >= mInterval)
	{
		mLastTime = mCurrentTime;
		return true;
	}
	return false;
}

void Timer::Tick(void (*funcPtr)())
{
	if (this->Tick())
		funcPtr();
}

void Timer::Interval(double ms)
{
	mInterval = ms;
}

void Timer::Start()
{
	mStarted = true;
	mPaused = false;
	mStartTicks = SDL_GetTicks();
}

void Timer::Stop()
{
	mStarted = false;
	mPaused = false;
}

void Timer::Pause()
{
	if ((mStarted) && (mPaused == false))
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks;
	}
}

void Timer::UnPause()
{
	if (mPaused)
	{
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}

double Timer::Now()
{
	if (mStarted)
	{
		if (mPaused)
			return (mPausedTicks) / 1000.0;
		else
			return (SDL_GetTicks() - mStartTicks) / 1000.0;
	}
	return 0;
}

bool Timer::IsPaused()
{
	return this->mPaused;
}
