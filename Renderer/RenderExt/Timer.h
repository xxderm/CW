#pragma once
#ifndef TIMER_HEADER
#define TIMER_HEADER
#include <SDL.h>

class Timer
{
public:
	/**
	 * Конструктор по умолчанию.
	*/
	Timer();

	/**
	 * Метод проверяет текущее время с интервалом.
	 * @return Статус проверки интервала с текущим временем.
	*/
	bool Tick();

	/**
	 * Метод вызывает указатель на функцию по интервалу.
	*/
	void Tick(void (*funcPtr)());

	/**
	 * Метод задает интервал тика таймера.
	 * @param ms Время в секундах.
	*/
	void Interval(double ms);

	/**
	 * Метод запускает таймер.
	*/
	void Start();

	/**
	 * Метод останавливает таймер.
	*/
	void Stop();

	/**
	 * Метод приостанавливает таймер.
	*/
	void Pause();

	/**
	 * Метод восстанавливает работу таймера.
	*/
	void UnPause();

	/**
	 * Метод возвращает текущее время в секундах с начала работы таймера.
	 * @return Текущее время.
	*/
	double Now();
	
	/**
	 * Метод возвращает статус работы таймера.
	 * @return Статус работы.
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
