#include "DXUT.h"
#include "cJungleMob3.h"
#include "cReflexBullet.h"

cJungleMob3::cJungleMob3(Vec2 pos, vector<cBullet*>& bullets, float size)
	:cMob(pos, size), m_bullets(bullets)
{
	m_image = IMAGE->MakeVecImg("jungle_mob3");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;

	speed = 2;
}

cJungleMob3::~cJungleMob3()
{
}

void cJungleMob3::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (p1Count < 5)
	{
		if (t_Pattern1 == nullptr)
		{
			t_Pattern1 = new cTimer(0.4, [&]()->void {
				Vec2 dir;
				Vec2 dirs[4] = { Vec2(-1, -1), Vec2(-1, 1), Vec2(1, 1), Vec2(1, -1) };
				for (int i = 0; i <= 5; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						dir = dirs[j];
						m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_jungle_mob3", "jungle_mob3_effect", "mob", m_damage, 0.5, 400, true));
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
	m_pos += {speed * dir_x, speed * dir_y};
}

void cJungleMob3::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}
