#include  "DXUT.h"
#include "cChurchBoss.h"
#include "cMBullet.h"

cChurchBoss::cChurchBoss(Vec2 pos, vector<cBullet*>& bullet, float size)
	: cMob(pos, size), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("church_boss");
	mobType = "Boss";
	m_damage = 1;

	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;

	isStop = false;
	pattern1 = true;
	pattern2 = false;
	disappear = false;
}

cChurchBoss::~cChurchBoss()
{
}

void cChurchBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();
	if (t_AppearDelay != nullptr) t_AppearDelay->Update();

	if (pattern1 && !pattern2)
	{
		if (t_Pattern1 == nullptr)
		{
			float interval = 0.1;
			angle += rad;
			t_Pattern1 = new cTimer(0.05, [&]()->void {
				Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
				direction = direction - m_pos;
				D3DXVec2Normalize(&direction, &direction);
				m_bullets.push_back(new cMBullet(m_pos, direction, "bullet_church_boss", "church_boss_effect", "boss", m_damage, 0.5, 400));
				t_Pattern1 = nullptr;
				});
		}
	}
	if (!pattern2)
	{
		if (t_Pattern2 == nullptr)
		{
			if (disappear)
			{
				if (t_AppearDelay == nullptr)
				{
					t_AppearDelay = new cTimer(3, [&]()->void {
						isStop = false;
						index = 0;
						m_image = IMAGE->MakeVecImg("church_boss");
						disappear = false;
						t_AppearDelay = nullptr;
						});
				}
			}
			else
			{
				t_Pattern2 = new cTimer(7, [&]()->void {
					pattern2 = true;
					t_Pattern2 = nullptr;
					});
			}
		}
	}
	else if (pattern2)
	{
		if (t_Pattern2 == nullptr)
		{
			isStop = true;
			disappear = true;
			m_image = IMAGE->MakeVecImg("church_boss_disappear");
			CAM->ZoomCam(0.1, 2, m_pos, true);

			t_Pattern2 = new cTimer(3, [&]() ->void {
				index = 0;
				reverse(m_image.begin(), m_image.end());
				float random_x, random_y;
				while (true)
				{
					random_x = rand() % WINSIZEX;
					random_y = rand() % WINSIZEY;

					if ((random_x > 40 && random_x < WINSIZEX - 40) && (random_y > 300 && random_y < WINSIZEY - 40))
						if (SCENE->Array[(int)random_y][(int)random_x] == 0)
						{
							m_pos = { random_x, random_y };
							CAM->ZoomCam(0.1, 2, m_pos, true);
							break;
						}

				}
				pattern2 = false;
				t_Pattern2 = nullptr;
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