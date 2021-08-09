#include  "DXUT.h"
#include "cIceBoss.h"
#include "cMBullet.h"
#include "cReflexBullet.h"

cIceBoss::cIceBoss(Vec2 pos, vector<cBullet*>& bullet, float size)
	: cMob(pos, size), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("ice_boss");
	mobType = "Boss";
	p1Count = 0;
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
	pattern2 = false;
	dashStart = false;
	speed = 1;
}

cIceBoss::~cIceBoss()
{
}

void cIceBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();

	if (SCENE->coloring_per >= 50 && !pattern2)
	{
		pattern2 = true;
	}

	if (pattern2 && !dashStart)
	{
		pattern1 = false;
		isStop = true;
		for (auto iter : m_bullets)
		{
			iter->m_Dir = *D3DXVec2Normalize(&(m_pos - iter->m_pos), &(m_pos - iter->m_pos)) * 5;
			if (D3DXVec2Length(&Vec2(m_pos - iter->m_pos)) <= (m_image.front()->info.Width / 2) * m_size)
			{
				iter->isDestroy = true;
			}
		}
		if (t_Pattern2 == nullptr)
			t_Pattern2 = new cTimer(1, [&]()->void {
			dashStart = true;
			isStop = false;
			speed = 10;
			t_Pattern2 = nullptr;
				});
	}

	else if (pattern1)
	{
		if (p1Count >= 5)
		{
			pattern1 = false;
			if (t_Pattern1 == nullptr)
				t_Pattern1 = new cTimer(3, [&]()->void {
				pattern1 = true;
				p1Count = 0;
				t_Pattern1 = nullptr;
					});
		}
		if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.5, [&]()->void {
			float rand_x = rand() % 4 - 1;
			if (rand_x == 0) rand_x = -2;
			float rand_y = rand() % 4 - 1;
			if (rand_y == 0) rand_y = -2;
			m_bullets.push_back(new cReflexBullet(m_pos, Vec2(rand_x, rand_y), "bullet_ice_boss", "ice_boss_effect", "boss", m_damage, 0.5, 400));
			p1Count++;
			t_Pattern1 = nullptr;
			});
	}

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
		if (dashStart)
		{
			CAM->ShakeCam(0.5f);
			XFire();
		}
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
		if (dashStart)
		{
			CAM->ShakeCam(0.5f);
			XFire();
		}
	}
	if (!isStop)
		m_pos += {speed* dir_x, speed* dir_y};
}

void cIceBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}

void cIceBoss::XFire()
{
	Vec2 dir[4] = { Vec2(-1, -1), Vec2(-1, 1) , Vec2(1, -1) ,Vec2(1, 1) };

	for (int i = 0; i < 4; i++)
		m_bullets.push_back(new cMBullet(m_pos, dir[i], "bullet_ice_boss", "ice_boss_effect", "boss", m_damage, 0.5, 400));
}