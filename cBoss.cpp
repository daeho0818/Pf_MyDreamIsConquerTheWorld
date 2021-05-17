#include  "DXUT.h"
#include "cBoss.h"
#include "cMBullet.h"

cBoss::cBoss(Vec2 pos, vector<cBullet*>& bullet)
	: cMob(pos), m_bullets(bullet)
{
	mobType = "Boss";
	m_damage = 1;
	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cBoss::~cBoss()
{
	SAFE_DELETE(t_Pattern1);
	SAFE_DELETE(t_Pattern2);
}

string cBoss::ChkOut()
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

void cBoss::CircleBullet()
{
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	for (int i = 0; i < 365; i++, angle += rad)
	{
		if (i == rand() % 365)
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * 5), m_pos.y + (sinf(angle) * 5));
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cMBullet(m_pos, direction, m_damage, 5, 400));
		}
	}
}

void cBoss::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();

	if (pattern1)
	{
		if (count < 10)
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.5, [&]()->void {
				isStop = true;
				count++;
				t_Pattern1 = nullptr;
				});
		}
		else
		{
			count = 0;
			pattern1 = false;
			isStop = false;
		}
	}
	else
	{
		if (t_Pattern2 == nullptr) t_Pattern2 = new cTimer(10, [&]()->void {
			pattern1 = true;
			t_Pattern2 = nullptr;
			isStop = true;
			});
	}

	if (isStop) {CircleBullet(); }

	if (INPUT->KeyDown(VK_RETURN)) CircleBullet();

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

void cBoss::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("Boss"), m_pos);
}