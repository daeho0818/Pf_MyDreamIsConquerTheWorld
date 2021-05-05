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
	for (auto iter : m_bullets) iter->Update();
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
