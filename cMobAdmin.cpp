#include "DXUT.h"
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

cMobAdmin::cMobAdmin(cPlayer* player, vector<cBullet*>& bullet, string stage)
	:m_player(player), m_bullets(bullet), stage(stage)
{
	Vec2 dir[4] = { Vec2(1, 1), Vec2(1, -1), Vec2(-1, 1), Vec2(-1, -1) };

	isDestroy = false;
	if (stage == "cChurchScene")
	{
		m_mobs.push_back(new cChurchMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cChurchMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cChurchBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
	}
	else if (stage == "cCityScene")
	{
		m_mobs.push_back(new cCityMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cCityMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cCityBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
	}
	else if (stage == "cCityNightScene")
	{
		m_mobs.push_back(new cCityNightMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cCityNightMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cCityNightBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
	}
	else if (stage == "cDesertScene")
	{
		m_mobs.push_back(new cDesertMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cDesertMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cDesertBoss1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
		m_mobs.push_back(new cDesertBoss2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[3].x;
		m_mobs.back()->dir_y = dir[3].y;
	}
	else if (stage == "cIceScene")
	{
		m_mobs.push_back(new cIceMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cIceMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cIceBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
	}
	else if (stage == "cJungleScene")
	{
		m_mobs.push_back(new cJungleMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cJungleMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cJungleMob3({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
		m_mobs.push_back(new cJungleBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[3].x;
		m_mobs.back()->dir_y = dir[3].y;
	}
	else if (stage == "cOceanScene")
	{
		m_mobs.push_back(new cOceanMob1({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[0].x;
		m_mobs.back()->dir_y = dir[0].y;
		m_mobs.push_back(new cOceanMob2({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 1.5));
		m_mobs.back()->dir_x = dir[1].x;
		m_mobs.back()->dir_y = dir[1].y;
		m_mobs.push_back(new cOceanBoss({ WINSIZEX / 2, WINSIZEY / 2 }, m_bullets, 2));
		m_mobs.back()->dir_x = dir[2].x;
		m_mobs.back()->dir_y = dir[2].y;
	}
}

cMobAdmin::~cMobAdmin()
{
	SAFE_DELETE(t_DeadDelay);
	for (auto iter : m_mobs)
	{
		SAFE_DELETE(iter->m_Ani);
		SAFE_DELETE(iter->t_Pattern1);
		SAFE_DELETE(iter->t_Pattern2);
		SAFE_DELETE(iter->t_Pattern3);
		SAFE_DELETE(iter);
	}
	m_mobs.clear();
}

void cMobAdmin::Update()
{
	if (t_DeadDelay != nullptr) t_DeadDelay->Update();

	for (auto iter : m_mobs)
	{
		iter->Update();

		if (iter->mobType == "Boss")
		{
			bossPos = iter->m_pos;
			if (stage == "cCityScene")
			{
				((cCityBoss*)(iter))->playerPos = m_player->m_pos;
			}
		}

		if (SCENE->Array[(int)iter->m_pos.y][(int)iter->m_pos.x] == 4)
		{
			if (stage == "cChurchScene")
			{
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "church_dead", 0.05);
			}
			else if (stage == "cCityScene")
			{
				if (iter->mobType == "Boss")
				{
					if (((cCityBoss*)(iter))->moveToTarget)
					{
						continue;
					}
				}
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "city_dead", 0.05);
			}
			else if (stage == "cCityNightScene")
			{
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "city(night)_dead", 0.05);
			}
			else if (stage == "cDesertScene")
			{
				if (iter->mobName == "gold")
					PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "desert_gold_dead", 0.05);
				else if (iter->mobName == "silver")
					PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "desert_silver_dead", 0.05);
			}
			else if (stage == "cIceScene")
			{
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "ice_dead", 0.05);
			}
			else if (stage == "cJungleScene")
			{
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "jungle_dead", 0.05);
			}
			else if (stage == "cOceanScene")
			{
				PART->AddParticle(iter->m_pos, (iter->mobType == "Boss") ? 0.7 : 0.3, "ocean_dead", 0.05);
			}

			if (iter->mobType == "Boss")
			{
				CAM->ShakeCam(0.3);
				CAM->ZoomCam(0.05, 0.05, { WINSIZEX / 2, WINSIZEY / 2 });
			}

			iter->isDestroy = true;
		}
	}
	IsDestroy();
}

void cMobAdmin::Render()
{
	for (auto iter : m_mobs) iter->Render();
}

void cMobAdmin::UIRender()
{
}

void cMobAdmin::IsDestroy()
{
	for (auto& iter = m_mobs.begin(); iter != m_mobs.end();)
	{
		if ((*iter)->isDestroy)
		{
			SOUND->Play("e_dead");
			SAFE_DELETE((*iter)->m_Ani);
			SAFE_DELETE((*iter)->t_Pattern1);
			SAFE_DELETE(*iter);
			iter = m_mobs.erase(iter);
		}
		else
			iter++;
	}
}

void cMobAdmin::Animation()
{
	for (auto iter : m_mobs)
	{
		repeat = true;
		if (iter->mobType == "Boss")
		{
			if (stage == "cChurchScene")
			{
				if ((dynamic_cast<cChurchBoss*>(iter))->disappear)
					repeat = false;
				else
					repeat = true;
			}
		}

		if (iter->m_Ani != nullptr) iter->m_Ani->Update();

		if (iter->m_Ani == nullptr) iter->m_Ani = new cTimer(0.1, [&]()->void {

			if (iter->index < iter->m_image.size() - 1)
			{
				iter->index++;
			}
			else
			{
				if (repeat)
					iter->index = 0;
			}
			iter->m_Ani = nullptr;
			});
	}
}