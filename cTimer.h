#pragma once
class cTimer
{
public:
	cTimer(float time, function<void()> func, bool loop = false, int count = 0);
	~cTimer();

	int m_count;
	int m_count_t = 0;
	float m_time;
	float m_curtime;
	float m_oldtime;
	bool b_loop;
	function<void()> func;

	void Update();
};