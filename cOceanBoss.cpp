#include  "DXUT.h"
#include "cOceanBoss.h"
#include "cMBullet.h"

cOceanBoss::cOceanBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("ocean_boss");
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = true;
}

cOceanBoss::~cOceanBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(m_Ani);
}

void cOceanBoss::Update()
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
		if (t_Pattern1 == nullptr)
		{
			t_Pattern1 = new cTimer(0.005, [&]()->void {
				for (int i = 0; i < 4; i++)
				{
					Vec2 dir;

					switch (dirIndex)
					{
					case 0:
						dir = Vec2(-1, -1) - m_pos;
						break;
					case 1:
						dir = Vec2(-1, WINSIZEY) - m_pos;
						break;
					case 2:
						dir = Vec2(WINSIZEX, -1) - m_pos;
						break;
					case 3:
						dir = Vec2(WINSIZEX, WINSIZEY) - m_pos;
						break;
					}
					dirIndex++;

					if (dirIndex == 4) dirIndex = 0;

					D3DXVec2Normalize(&dir, &dir);

					m_bullets.push_back(new cMBullet(m_pos, dir, "bullet_ocean_boss", "ocean_boss_effect", m_damage, 0.5, 5000));
				}
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

void cOceanBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}