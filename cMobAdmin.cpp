#include "DXUT.h"
#include "cBoss.h"
#include "cMobAdmin.h"

cMobAdmin::cMobAdmin()
{
	m_mobs.push_back(new cBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
}

cMobAdmin::~cMobAdmin()
{
	for (auto iter : m_mobs) SAFE_DELETE(iter);
	m_mobs.clear();
}

void cMobAdmin::Update()
{
	for (auto iter : m_mobs)
	{
		iter->Update();
		if (iter->mobType == "Boss") { bossPos = iter->m_pos; boss = iter; }
	}
}

void cMobAdmin::Render()
{
	for (auto iter : m_mobs)
	{
		iter->Render();
	}
}

void cMobAdmin::UIRender()
{

}