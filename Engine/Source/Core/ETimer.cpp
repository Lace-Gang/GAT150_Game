#include "ETimer.h"

void Time::Tick()
{
	clock::duration duration = clock::now() - m_startTime;
	m_time = duration.count() / (float)clock::duration::period::den; //den = denominator

	duration = clock::now() - m_frameTime;
	m_deltaTime = duration.count() / (float)clock::duration::period::den;

	m_frameTime = clock::now();
}