#include "DXUT.h"
#include "cBulletAdmin.h"

cBulletAdmin::cBulletAdmin()
{
}

cBulletAdmin::~cBulletAdmin()
{
	for (auto iter : m_bullets) SAFE_DELETE(iter);
	m_bullets.clear();
}

void cBulletAdmin::Update()
{
	int random[2] = { rand() % 2, rand() % 2 };

	int random_x = 0, random_y = 0;

	if (random[0] == 0)
	{
		random_x = rand() % -20;
	}
	else if (random[0] == 1)
	{
		random_x = rand() % 20;
	}
	if (random[1] == 0)
	{
		random_y = rand() % -20;
	}
	else if (random[1] == 1)
	{
		random_y = rand() % 20;
	}

	for (auto iter : m_bullets)
	{
		iter->Update();

		PART->AddEffect(Vec2(iter->m_pos.x + random_x, iter->m_pos.y + random_y), 1, iter->effectName);
	}
	IsOut();
	IsDestroy();
}

void cBulletAdmin::Render()
{
	for (auto iter : m_bullets) iter->Render();
}

void cBulletAdmin::IsOut()
{
	size_t size = m_bullets.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_bullets[i];
		if (iter->IsOutMap())
		{
			SAFE_DELETE(iter);
			m_bullets.erase(m_bullets.begin() + i);
			i--; size--;
		}
	}
}

void cBulletAdmin::IsDestroy()
{
	size_t size = m_bullets.size();
	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_bullets[i];
		if (iter->isDestroy)
		{
			SAFE_DELETE(iter);
			m_bullets.erase(m_bullets.begin() + i);
			i--; size--;
		}
	}
}
