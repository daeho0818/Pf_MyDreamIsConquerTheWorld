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
}

cIceBoss::~cIceBoss()
{
}

void cIceBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();

	if (pattern1)
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
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	if (!isStop)
		m_pos += {1 * dir_x, 1 * dir_y};
}

void cIceBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}