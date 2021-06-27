#include  "DXUT.h"
#include "cCityNightBoss.h"
#include "cMBullet.h"

cCityNightBoss::cCityNightBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("city(night)_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cCityNightBoss::~cCityNightBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(m_Ani);
}

void cCityNightBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (m_Ani == nullptr)
	{
		m_Ani = new cTimer(0.1, [&]()->void {
			index++;
			if (index == m_image.size()) index = 0;
			m_Ani = nullptr;
			});
	}
	if (m_Ani != nullptr) m_Ani->Update();

	if (pattern1)
	{
		if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.02, [&]()->void {
			angle += rad;
			t_Pattern1 = nullptr;
			});
	}

	Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5)), m_pos.y + (sinf(angle) * (5)));
	direction = direction - m_pos;
	D3DXVec2Normalize(&direction, &direction);
	m_bullets.push_back(new cMBullet(m_pos, direction, "bullet_city(night)_boss", "city(night)_boss_effect", m_damage, 0.4, 2500));

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	if (!isStop)
		m_pos += {1 * dir_x, 1 * dir_y};
}

void cCityNightBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}