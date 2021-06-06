#include "DXUT.h"
#include "cCityNightMob1.h"

cCityNightMob1::cCityNightMob1(Vec2 pos)
	:cMob(pos)
{
	m_image = IMAGE->MakeVecImg("city(night)_mob1");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cCityNightMob1::~cCityNightMob1()
{
	SAFE_DELETE(m_Ani);
}

void cCityNightMob1::Update()
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

void cCityNightMob1::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 1.5);
}
