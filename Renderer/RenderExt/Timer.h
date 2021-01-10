#pragma once
#ifndef TIMER_HEADER
#define TIMER_HEADER
#include <boost/timer.hpp>

class Timer
{
public:
	bool OnTick();
	void Interval();
	void Start();
	void Stop();
private:
	boost::timer mTimer;
};

#endif // !TIMER_HEADER
