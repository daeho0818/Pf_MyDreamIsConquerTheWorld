#include  "DXUT.h"
#include "cJungleBoss.h"
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
	pattern1 = false;
	pattern2 = true;
	pattern3 = false;
}

cJungleBoss::~cJungleBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(t_Pattern2);
}

string cJungleBoss::ChkOut()
{
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == 2)
		return "Right";
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == 2)
		return "Left";
	if (SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == 2)
		return "Down";
	if (SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == 2)
		return "Up";
	return "";
}

void cJungleBoss::CircleBullet(float interval, bool random)
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
				m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 5, 400));
			}
		}
		else
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 5, 400));
		}
	}
}

void cJungleBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();
	if (t_Pattern3 != nullptr) t_Pattern3->Update();
	if (m_Ani != nullptr) m_Ani->Update();

	if (pattern1)
	{
		if (p1Count < 10)
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.5, [&]()->void {
				isStop = true;
				p1Count++;
				t_Pattern1 = nullptr;
				});
		}
		else
		{
			p1Count = 0;
			pattern1 = false;
			isStop = false;
			pattern3 = true;
		}
	}
	else
	{
		if (pattern2)
		{
			if (t_Pattern2 == nullptr) t_Pattern2 = new cTimer(10, [&]()->void {
				pattern1 = true;
				t_Pattern2 = nullptr;
				isStop = true;
				});
		}
	}
	if (pattern3)
	{
		if (p3Count < 3)
		{
			if (t_Pattern3 == nullptr) t_Pattern3 = new cTimer(1, [&]()->void {
				float temp = 5;
				p3Count++;
				CircleBullet(temp * p3Count);
				t_Pattern3 = nullptr;
				});
		}
		else
		{
			pattern3 = false;
			p3Count = 0;
		}
	}

	if (m_Ani == nullptr)
	{
		m_Ani = new cTimer(0.1, [&]()->void {
			index++;
			if (index == m_image.size()) index = 0;
			});
	}

	if (isStop) {CircleBullet(0, true); }

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
	RENDER->CenterRender(m_image[index], m_pos);
}