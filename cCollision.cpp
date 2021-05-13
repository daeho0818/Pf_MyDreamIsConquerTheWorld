#include "DXUT.h"
#include "cCollision.h"

cCollision::cCollision(vector<cBullet*>& bullet, vector<cMob*>& m_mobs, cPlayer* player, cItemAdmin* itemAd)
	:m_bullets(bullet), m_player(player), m_mobs(m_mobs), m_itemAd(itemAd), m_item(m_itemAd->m_items)
{
}

cCollision::~cCollision()
{
}

void cCollision::Update()
{
	MPColl();
	MPBColl();
	MBPColl();
	IPColl();
}

void cCollision::MPColl()
{
	for (auto iter = m_mobs.begin(); iter != m_mobs.end();)
	{
		if (50 + (*iter)->m_size >= D3DXVec2Length(&(m_player->m_pos - (*iter)->m_pos)))
		{
			if (b_PMColl)
			{
				if ((*iter)->mobType == "Boss")
					b_PMColl = false;
				if (!m_player->invincibility)
				{
					m_player->hp -= (*iter)->m_damage;
					m_player->EatItem("Invincibility");
				}
			}
			else
			{
				if ((*iter)->mobType == "Boss") b_PMColl = true;
			}
		}
		iter++;
	}
}

void cCollision::MPBColl()
{
}

void cCollision::MBPColl()
{
	for (auto iter = m_bullets.begin(); iter != m_bullets.end();)
	{
		if ((*iter)->bulletType == "mob")
		{
			if (7 + (*iter)->size >= D3DXVec2Length(&(m_player->m_pos - (*iter)->m_pos)))
			{
				if (!m_player->invincibility)
				{
					m_player->hp -= (*iter)->m_Damage;
					(*iter)->isDestroy = true;
					m_player->EatItem("Invincibility");
				}
			}
		}
		iter++;
	}
}

void cCollision::IPColl()
{
	for (auto iter = m_item.begin(); iter != m_item.end();)
	{
		if (7 + (*iter)->m_size >= D3DXVec2Length(&(m_player->m_pos - (*iter)->m_pos)))
		{
			m_player->itemName = (*iter)->itemName;
			(*iter)->isDestroy = true;
		}
		iter++;
	}
}
