#include  "DXUT.h"
#include "cCityBoss.h"
#include "cMBullet.h"
#include "cReflexBullet.h"

cCityBoss::cCityBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("city_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cCityBoss::~cCityBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(m_Ani);
}

void cCityBoss::CircleBullet(float interval, bool random)
{
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	for (int i = 0; i < 365; i++, angle += rad)
	{
		if (random)
		{
			if (i == rand() % 365)
			{
				Vec2 direction = Vec2(m_pos.x + (cosf(angle) * 5), m_pos.y + (sinf(angle) * 5));
				direction = direction - m_pos;
				D3DXVec2Normalize(&direction, &direction);
				m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 0.1, 400));
			}
		}
		else
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 0.1, 400));
		}
	}
}

void cCityBoss::Update()
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
		if (p1Count < 10)
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.01, [&]()->void {
				isStop = true;
				p1Count++;
				t_Pattern1 = nullptr;
				});
		}
		else
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(7, [&]()->void {
				p1Count = 0;
				isStop = false;
				t_Pattern1 = nullptr;
				});
		}
	}

	if (isStop)
	{
		for (int i = 0; i < 1000; i++, angle += rad)
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (10)), m_pos.y + 1);
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cReflexBullet(m_pos, direction,IMAGE->FindImage("bullet_enemy"), m_damage, 0.1, 400, true));
			
			direction = Vec2(m_pos.x + (cosf(angle) * (5)), m_pos.y - 1);
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cReflexBullet(m_pos, direction, IMAGE->FindImage("bullet_enemy"), m_damage, 0.1, 400, true));
			
			isStop = false;
		}
	}

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

void cCityBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}