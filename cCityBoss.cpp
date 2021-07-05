#include  "DXUT.h"
#include "cCityBoss.h"
#include "cMBullet.h"
#include "cReflexBullet.h"

cCityBoss::cCityBoss(Vec2 pos, vector<cBullet*>& bullet, float size)
	: cMob(pos, size), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("city_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
	pattern2 = false;
}

cCityBoss::~cCityBoss()
{
	SAFE_DELETE(t_Pattern2);
}

void cCityBoss::CircleBullet(float interval, Vec2 pos)
{
	if (pos == Vec2(0, 0)) pos = m_pos;
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	for (int i = 0; i < 365; i++, angle += rad)
	{
		Vec2 direction = Vec2(pos.x + (cosf(angle) * (5 + interval)), pos.y + (sinf(angle) * (5 + interval)));
		direction = direction - pos;
		D3DXVec2Normalize(&direction, &direction);
		m_bullets.push_back(new cMBullet(pos, direction, "bullet_city_boss", "city_boss_effect", m_damage, 0.5, 400));
	}
}

void cCityBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();

	if (pattern1)
	{
		if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(7, [&]()->void {
			Vec2 dir = Vec2(0, 0) - m_pos;
			D3DXVec2Normalize(&dir, &dir);
			m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_city_boss", "city_boss_effect", m_damage, 0.5, 400));
			bullets[0] = m_bullets.back();

			dir = Vec2(WINSIZEX, 0) - m_pos;
			D3DXVec2Normalize(&dir, &dir);
			m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_city_boss", "city_boss_effect", m_damage, 0.5, 400));
			bullets[1] = m_bullets.back();

			dir = Vec2(0, WINSIZEY) - m_pos;
			D3DXVec2Normalize(&dir, &dir);
			m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_city_boss", "city_boss_effect", m_damage, 0.5, 400));
			bullets[2] = m_bullets.back();

			dir = Vec2(WINSIZEX, WINSIZEY) - m_pos;
			D3DXVec2Normalize(&dir, &dir);
			m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_city_boss", "city_boss_effect", m_damage, 0.5, 400));
			bullets[3] = m_bullets.back();

			p1Count++;
			t_Pattern1 = nullptr;
			pattern2 = true;
			pattern1 = false;
			});
	}
	if (pattern2)
	{
		if (t_Pattern2 == nullptr)
		{
			t_Pattern2 = new cTimer(2, [&]()->void {
				for (auto iter : bullets)
				{
					CircleBullet(1, iter->m_pos);
				}
				t_Pattern2 = nullptr;
				pattern2 = false;
				pattern1 = true;
				memset(bullets, 0, sizeof(bullets));
				});
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
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}