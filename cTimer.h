#pragma once
class cTimer
{
public:
	cTimer(double time, function<void()> func, bool loop = false, int count = 0);
	~cTimer();

	int m_count;
	int m_count_t = 0;
	double m_time;
	double m_curtime;
	double m_oldtime;
	bool b_loop;
	function<void()> func;

	void Update();
};