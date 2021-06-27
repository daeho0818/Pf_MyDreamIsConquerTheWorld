#include "DXUT.h"
#include "cDesertMob1.h"
#include "cReflexBullet.h"

cDesertMob1::cDesertMob1(Vec2 pos, vector<cBullet*>& bullets)
	:cMob(pos), m_bullets(bullets)
{
	m_image = IMAGE->MakeVecImg("desert_mob1");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cDesertMob1::~cDesertMob1()
{
	SAFE_DELETE(m_Ani);
}

void cDesertMob1::Update()
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
				for (int i = -5; i <= 5; i++)
				{
					if (i != 0)
					{
						dir = { 1 * (float)i, 0 };
						D3DXVec2Normalize(&dir, &dir);
						m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_desert_mob1", "desert_mob1_effect", m_damage, 0.5, 400, true));
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

void cDesertMob1::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 1.5);
}