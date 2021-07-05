#include  "DXUT.h"
#include "cChurchBoss.h"
#include "cMBullet.h"

cChurchBoss::cChurchBoss(Vec2 pos, vector<cBullet*>& bullet, float size)
	: cMob(pos, size), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("church_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cChurchBoss::~cChurchBoss()
{
}

void cChurchBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();

	if (pattern1)
	{
		if (t_Pattern1 == nullptr)
		{
			float interval = 0.1;
			angle += rad;
			t_Pattern1 = new cTimer(0.05, [&]()->void {
				Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
				direction = direction - m_pos;
				D3DXVec2Normalize(&direction, &direction);
				m_bullets.push_back(new cMBullet(m_pos, direction,"bullet_church_boss", "church_boss_effect",  m_damage, 0.5, 400));
				t_Pattern1 = nullptr;
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

void cChurchBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}