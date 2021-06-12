#pragma once
#include "cPlayer.h"
#include "cItemAdmin.h"
#include "cMob.h"
#include "cItem.h"
class cCollision
{
public:
	cCollision(vector<cBullet*>& bullet, vector<cMob*>& mobs, cPlayer* player, cItemAdmin* itemAd);
	~cCollision();

	vector<cBullet*>& m_bullets;
	vector<cMob*>& m_mobs;
	cPlayer* m_player;
	cItemAdmin* m_itemAd;
	vector<cItem*>& m_item;

	void Update();

	void MPColl();
	void MPBColl();
	void MBPColl();
	void IPColl();
};

