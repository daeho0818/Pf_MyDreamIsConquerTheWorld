#include  "DXUT.h"
#include "cDesertBoss1.h"
#include "cMBullet.h"

cDesertBoss1::cDesertBoss1(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("desert_boss1");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cDesertBoss1::~cDesertBoss1()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(m_Ani);
}

void cDesertBoss1::Update()
{
	if (m_Ani == nullptr)
	{
		m_Ani = new cTimer(0.1, [&]()->void {
			index++;
			if (index == m_image.size()) index = 0;
			m_Ani = nullptr;
			});
	}
	if (m_Ani != nullptr) m_Ani->Update();

	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (pattern1)
	{
		if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(3, [&]()->void {
			Vec2 dir;
			for (float i = -10; i < 10; i++)
			{
				dir = Vec2(-1, -1);
				if (i != 0) dir = Vec2(-1 * i / 10, -1);
				m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_desert_boss1", "desert_boss1_effect", m_damage, 0.5, 400));
				dir = Vec2(-1, 1);
				if (i != 0) dir = Vec2(-1 * i / 10, 1);
				m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_desert_boss1", "desert_boss1_effect", m_damage, 0.5, 400));
				dir = Vec2(1, -1);
				if (i != 0) dir = Vec2(1, -1 * i / 10);
				m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_desert_boss1", "desert_boss1_effect", m_damage, 0.5, 400));
				dir = Vec2(-1, -1);
				if (i != 0) dir = Vec2(-1, -1 * i / 10);
				m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_desert_boss1", "desert_boss1_effect", m_damage, 0.5, 400));
			}
			t_Pattern1 = nullptr;
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
	if (!isStop)
		m_pos += {1 * dir_x, 1 * dir_y};
}

void cDesertBoss1::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}