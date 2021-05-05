#pragma once
#include "cPlayer.h"
#include "cItemAdmin.h"
#include "cMob.h"
#include "cItem.h"
class cCollision
{
public:
	cCollision(vector<cMob*>& mobs, cPlayer* player, cItemAdmin* itemAd);
	~cCollision();

	vector<cMob*> m_mobs;
	cPlayer* m_player;
	cItemAdmin* m_itemAd;
	vector<cItem*>& m_item;

	bool b_PMColl = true;

	void Update();

	void MPColl();
	void MPBColl();
	void IPColl();
};

