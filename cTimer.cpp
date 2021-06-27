#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(double time, function<void()> func, bool loop, int count)
	:m_time(time * 1000), func(func), b_loop(loop), m_count(count)
{
	m_oldtime = GetTickCount();
	m_curtime = m_oldtime;
}

cTimer::~cTimer()
{
}

void cTimer::Update()
{
	m_curtime = GetTickCount();
	if (m_curtime - m_oldtime >= m_time)
	{
		func();
		if (b_loop)
		{
			if (m_count == 0)
				m_oldtime = GetTickCount();
			else
			{
				if (m_count_t < m_count)
				{
					m_oldtime = GetTickCount();
					m_count_t++;
				}
				else
					delete this;
			}
		}
		else
			delete this;
	}
}
