#include "stdafx.h"
#include "ScopedTimer.h"

ScopedTimer::ScopedTimer()
{
	m_startTime = m_clock.now();
	printf("Time object was initialized\n");
}


ScopedTimer::~ScopedTimer()
{
	std::chrono::duration<double, std::milli> dur = m_clock.now() - m_startTime;
	printf("Base object destructor called after: %4.2fms\n", dur);
}
