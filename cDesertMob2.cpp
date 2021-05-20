#include "DXUT.h"
#include "cDesertMob2.h"

cDesertMob2::cDesertMob2(Vec2 pos)
	:cMob(pos)
{
	m_image = IMAGE->MakeVecImg("desert_mob2");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cDesertMob2::~cDesertMob2()
{
}

void cDesertMob2::Update()
{
	if (m_Ani != nullptr) m_Ani->Update();

	if (m_Ani == nullptr)
	{
		m_Ani = new cTimer(0.1, [&]()->void {
			index++;
			if (index == m_image.size()) index = 0;
			m_Ani = nullptr;
			});
	}

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	m_pos += {1 * dir_x, 1 * dir_y};
}

void cDesertMob2::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 1.5);
}


string cDesertMob2::ChkOut()
{
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == 2)
		return "Right";
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == 2)
		return "Left";
	if (SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == 2)
		return "Down";
	if (SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == 2)
		return "Up";
	return "";
}