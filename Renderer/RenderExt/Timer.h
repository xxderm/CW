#pragma once
#ifndef TIMER_HEADER
#define TIMER_HEADER
#include <SDL.h>

class Timer
{
public:
	/**
	 * ����������� �� ���������.
	*/
	Timer();

	/**
	 * ����� ��������� ������� ����� � ����������.
	 * @return ������ �������� ��������� � ������� ��������.
	*/
	bool Tick();

	/**
	 * ����� �������� ��������� �� ������� �� ���������.
	*/
	void Tick(void (*funcPtr)());

	/**
	 * ����� ������ �������� ���� �������.
	 * @param ms ����� � ��������.
	*/
	void Interval(double ms);

	/**
	 * ����� ��������� ������.
	*/
	void Start();

	/**
	 * ����� ������������� ������.
	*/
	void Stop();

	/**
	 * ����� ���������������� ������.
	*/
	void Pause();

	/**
	 * ����� ��������������� ������ �������.
	*/
	void UnPause();

	/**
	 * ����� ���������� ������� ����� � �������� � ������ ������ �������.
	 * @return ������� �����.
	*/
	double Now();
	
	/**
	 * ����� ���������� ������ ������ �������.
	 * @return ������ ������.
	*/
	bool IsPaused();
private:
	int mStartTicks = 0;
	int mPausedTicks = 0;
	bool mPaused = false;
	bool mStarted = false;
	double mInterval = 0.0;
	double mCurrentTime = 0.0;
	double mLastTime = 0.0;
};

#endif // !TIMER_HEADER
