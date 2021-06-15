#include "DXUT.h"
#include "cMob.h"

string cMob::ChkOut()
{
	if (m_pos.x >= WINSIZEX - 3) return "Left";
	if (m_pos.x <= 0 + 3) return "Right";
	if (m_pos.y >= WINSIZEY - 3) return "Up";
	if (m_pos.y <= 0 + 3) return "Down";

	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == 2
		|| SCENE->Array[(int)m_pos.y][(int)m_pos.x + 2] == 2)
	{
		return "Right";
	}
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == 2
		|| SCENE->Array[(int)m_pos.y][(int)m_pos.x - 2] == 2)
	{
		return "Left";
	}
	if (SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == 2
		|| SCENE->Array[(int)m_pos.y + 2][(int)m_pos.x] == 2)
	{
		return "Down";
	}
	if (SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == 2
		|| SCENE->Array[(int)m_pos.y - 2][(int)m_pos.x] == 2)
	{
		return "Up";
	}
	return "";
}