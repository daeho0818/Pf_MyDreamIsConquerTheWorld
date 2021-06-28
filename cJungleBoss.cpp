#include  "DXUT.h"
#include "cJungleBoss.h"
#include "cReflexBullet.h"
#include "cMBullet.h"

cJungleBoss::cJungleBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("jungle_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cJungleBoss::~cJungleBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(m_Ani);
}

void cJungleBoss::Update()
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
		if (p1Count < 5)
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.5, [&]()->void {
				isStop = true;
				Vec2 dir;
				for (int i = -(WINSIZEX / 2); i <= WINSIZEY / 2; i += WINSIZEY / 5)
				{
					dir = {-WINSIZEX, (float)i};
					D3DXVec2Normalize(&dir, &dir);
					m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_jungle_boss", "jungle_boss_effect", m_damage, 0.5, 400, true));

					dir = {WINSIZEX, (float)i};
					D3DXVec2Normalize(&dir, &dir);
					m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_jungle_boss", "jungle_boss_effect", m_damage, 0.5, 400, true));
				}
				p1Count++;
				t_Pattern1 = nullptr;
				});
		}
		else
		{
			isStop = false;
			if (t_Pattern1 == nullptr)
				t_Pattern1 = new cTimer(10, [&]()->void {
				p1Count = 0;
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

void cJungleBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}