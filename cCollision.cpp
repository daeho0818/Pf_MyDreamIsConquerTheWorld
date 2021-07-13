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
	float length;
	for (auto iter = m_mobs.begin(); iter != m_mobs.end();)
	{
		if ((*iter))
		{
			// Circle Collider 구현한거.. 남겨놓음...

			//length = (pow((*iter)->m_image.front()->info.Width, 2) +
			//	pow((*iter)->m_image.front()->info.Height, 2)) * (*iter)->m_size;
			//length /= 2;
			// 하고 그냥 length 넣지 말고 제곱근 넣으면 됨

			length = (*iter)->m_image.front()->info.Height / 2 * (*iter)->m_size;

			if (abs(m_player->m_pos.y - (*iter)->m_pos.y) <= (*iter)->m_image.front()->info.Height / 2 * (*iter)->m_size)
				length = (*iter)->m_image.front()->info.Height / 2 * (*iter)->m_size;

			else if (abs(m_player->m_pos.x - (*iter)->m_pos.x) <= (*iter)->m_image.front()->info.Width / 2 * (*iter)->m_size)
				length = (*iter)->m_image.front()->info.Width / 2 * (*iter)->m_size;

			length /= 1.5;

			if (length >= D3DXVec2Length(&Vec2(m_player->m_pos - (*iter)->m_pos)))
			{
				if (!m_player->invincibility && m_player->draw_line && !m_player->returning && m_player->hp > 0)
				{
					if (SCENE->Array[(int)m_player->m_pos.y][(int)m_player->m_pos.x] != 2)
					{
						DebugLog(L"MPColl");
						CAM->ShakeCam(0.3);
						if (m_player->hp > 1)
							SOUND->Play("attack", -3000);
						m_player->hp -= (*iter)->m_damage;
						m_player->returning = true;
						m_player->isAttacked = true;
					}
				}
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
			if (50 + (*iter)->size >= D3DXVec2Length(&Vec2(m_player->m_pos - (*iter)->m_pos)))
			{
				if (!m_player->invincibility && m_player->draw_line && !m_player->returning && m_player->hp > 0)
				{
					if (SCENE->Array[(int)m_player->m_pos.y][(int)m_player->m_pos.x] != 2)
					{
						DebugLog(L"MBPColl");
						CAM->ShakeCam(0.3);
						if (m_player->hp > 1)
							SOUND->Play("attack", -3000);
						m_player->hp -= (*iter)->m_Damage;
						m_player->returning = true;
						(*iter)->isDestroy = true;
						m_player->isAttacked = true;
					}
				}
			}
		}
		iter++;
	}
}

void cCollision::IPColl()
{
	float length;
	for (auto iter = m_item.begin(); iter != m_item.end();)
	{
		length = ((*iter)->m_image->info.Height / 2) * (*iter)->m_size;

		if (abs(m_player->m_pos.y - (*iter)->m_pos.y) <= (*iter)->m_image->info.Height / 2 * (*iter)->m_size)
			length = (*iter)->m_image->info.Height / 2 * (*iter)->m_size;

		else if (abs(m_player->m_pos.x - (*iter)->m_pos.x) <= (*iter)->m_image->info.Width / 2 * (*iter)->m_size)
			length = (*iter)->m_image->info.Width / 2 * (*iter)->m_size;

		if (length + (*iter)->m_size >= D3DXVec2Length(&Vec2(m_player->m_pos - (*iter)->m_pos)))
		{
			m_player->EatItem((*iter)->itemName);
			(*iter)->isDestroy = true;
		}
		iter++;
	}
}
