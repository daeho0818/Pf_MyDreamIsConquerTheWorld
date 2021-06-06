#include "DXUT.h"
#include "cBoss.h"
#include "cIceMob1.h"
#include "cIceMob2.h"
#include "cIceBoss.h"
#include "cChurchMob1.h"
#include "cChurchMob2.h"
#include "cChurchBoss.h"
#include "cCityMob1.h"
#include "cCityMob2.h"
#include "cCityBoss.h"
#include "cCityNightMob1.h"
#include "cCityNightMob2.h"
#include "cCityNightBoss.h"
#include "cDesertMob1.h"
#include "cDesertMob2.h"
#include "cDesertBoss1.h"
#include "cDesertBoss2.h"
#include "cJungleMob1.h"
#include "cJungleMob2.h"
#include "cJungleMob3.h"
#include "cJungleBoss.h"
#include "cOceanMob1.h"
#include "cOceanMob2.h"
#include "cOceanBoss.h"
#include "cMobAdmin.h"

cMobAdmin::cMobAdmin(vector<cBullet*>& bullet, string stage)
	:m_bullets(bullet)
{
	isDestroy = false;
	m_mobs.clear();
	string asdf = stage;
	if (stage == "cChurchScene")
	{
		m_mobs.push_back(new cChurchMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cChurchMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cChurchBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cCityScene")
	{
		m_mobs.push_back(new cCityMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cCityMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cCityBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cCityNightScene")
	{
		m_mobs.push_back(new cCityNightMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cCityNightMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cCityNightBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cDesertScene")
	{
		m_mobs.push_back(new cDesertMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cDesertMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cDesertBoss1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
		m_mobs.push_back(new cDesertBoss2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cIceScene")
	{
		m_mobs.push_back(new cIceMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cIceMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cIceBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cJungleScene")
	{
		m_mobs.push_back(new cJungleMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cJungleMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cJungleMob3({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cJungleBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
	else if (stage == "cOceanScene")
	{
		m_mobs.push_back(new cOceanMob1({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cOceanMob2({ WINSIZEX / 2, WINSIZEY / 2 }));
		m_mobs.push_back(new cOceanBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets));
	}
}

cMobAdmin::~cMobAdmin()
{
	for (auto iter : m_mobs) SAFE_DELETE(iter);
	m_mobs.clear();
}

void cMobAdmin::Update()
{
	for (auto iter = m_mobs.begin(); iter != m_mobs.end();)
	{
		if (*iter)
		{
			(*iter)->Update();

			if ((*iter)->mobType == "Boss") { bossPos = (*iter)->m_pos; boss = (*iter); }
			if (SCENE->Array[int((*iter)->m_pos.y)][int((*iter)->m_pos.x)] == 3)
			{
				isDestroy = true;
				(*iter)->isDestroy = true;
				iter = m_mobs.erase(iter);
				SAFE_DELETE(*iter);
			}
		}
		iter++;
	}
}

void cMobAdmin::Render()
{
	for (auto iter : m_mobs)
	{
		if (iter)
			iter->Render();
	}
}

void cMobAdmin::UIRender()
{

}