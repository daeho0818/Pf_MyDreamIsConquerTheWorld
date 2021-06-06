#include "DXUT.h"
#include "cMob.h"

string cMob::ChkOut()
{
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == 2)
	{
		return "Right";
	}
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == 2)
	{
		return "Left";
	}
	if (SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == 2)
	{
		return "Down";
	}
	if (SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == 2)
	{
		return "Up";
	}
	return "";
}