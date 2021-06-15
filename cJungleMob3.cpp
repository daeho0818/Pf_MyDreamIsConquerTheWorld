#include "DXUT.h"
#include "cJungleMob3.h"
#include "cReflexBullet.h"

cJungleMob3::cJungleMob3(Vec2 pos, vector<cBullet*>& bullets)
	:cMob(pos), m_bullets(bullets)
{
	m_image = IMAGE->MakeVecImg("jungle_mob3");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cJungleMob3::~cJungleMob3()
{
	SAFE_DELETE(m_Ani);
}

void cJungleMob3::Update()
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

	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (p1Count < 5)
	{
		if (t_Pattern1 == nullptr)
		{
			t_Pattern1 = new cTimer(0.4, [&]()->void {
				Vec2 dir;
				for (int i = 0; i <= 5; i++)
				{
					if (i != 0)
					{
						dir = {-1, -1};
						m_bullets.push_back(new cReflexBullet(m_pos, dir, IMAGE->FindImage("bullet_enemy1"), m_damage, 0.1, 400, true));
						dir = {-1, 1};
						m_bullets.push_back(new cReflexBullet(m_pos, dir, IMAGE->FindImage("bullet_enemy1"), m_damage, 0.1, 400, true));
						dir = {1, 1};
						m_bullets.push_back(new cReflexBullet(m_pos, dir, IMAGE->FindImage("bullet_enemy1"), m_damage, 0.1, 400, true));
						dir = {1, -1};
						m_bullets.push_back(new cReflexBullet(m_pos, dir, IMAGE->FindImage("bullet_enemy1"), m_damage, 0.1, 400, true));
					}
				}
				p1Count++;
				t_Pattern1 = nullptr;
				});

		}
	}
	else
	{
		if (t_Pattern1 == nullptr)
			t_Pattern1 = new cTimer(5, [&]() -> void { p1Count = 0; t_Pattern1 = nullptr; });
	}

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	m_pos += {2 * dir_x, 2 * dir_y};
}

void cJungleMob3::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 1.5);
}
