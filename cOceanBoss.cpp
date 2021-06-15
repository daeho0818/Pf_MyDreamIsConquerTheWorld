#include  "DXUT.h"
#include "cOceanBoss.h"
#include "cMBullet.h"

cOceanBoss::cOceanBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("ocean_boss");
	mobType = "Boss";
	m_damage = 1;
	speed = 2;
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

void cOceanBoss::CircleBullet(float interval, bool random)
{
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	for (int i = 0; i < 365; i++, angle += rad)
	{
		if (random)
		{
			if (i == rand() % 365)
			{
				Vec2 direction = Vec2(m_pos.x + (cosf(angle) * 5), m_pos.y + (sinf(angle) * 5));
				direction = direction - m_pos;
				D3DXVec2Normalize(&direction, &direction);
				m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 0.1, 400));
			}
		}
		else
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 0.1, 400));
		}
	}
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
				for (int i = 0; i < 360; i++)
				{
					Vec2 dir;

					if (i % 90 == 0)
					{
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
						m_bullets.push_back(new cMBullet(m_pos, dir, m_damage, 0.1, 5000));
					}
				}
				t_Pattern1 = nullptr;
				});
		}
	}


	if (isStop) { CircleBullet(0, true); }

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	if (!isStop)
		m_pos += {speed* dir_x, speed* dir_y};
}

void cOceanBoss::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 2);
}