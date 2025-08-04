#include "Timer.h"

can::Timer::Timer()
{
	QueryPerformanceFrequency(&m_large);
	m_freq = static_cast<double>(m_large.QuadPart);
	getStartTime();
}

can::Timer::~Timer()
{

}

void can::Timer::getStartTime()
{
	QueryPerformanceCounter(&m_large);
	m_start = m_large.QuadPart;
}

double can::Timer::getEndTime()
{
	QueryPerformanceCounter(&m_large);
	return static_cast<double>(m_large.QuadPart - m_start) * 1000 / m_freq;
}

void can::Timer::sleep(double ms)
{
	getStartTime();
	while (getEndTime() < ms);
}
