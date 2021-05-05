#pragma once
#include "cPlayer.h"
#include "cItem.h"
class cItemAdmin
{
public:
	cItemAdmin(cPlayer* player);
	~cItemAdmin();

	vector<cItem*> m_items;

	cPlayer* m_player;
	float CreatePercent;
	Vec2 itemPos;
	cTimer* t_Heal = nullptr;
	cTimer* t_Speed = nullptr;
	cTimer* t_Invincibility = nullptr;

	void Update();
	void Render();
	void CreateItem(string key);
	void IsDestroy();
};

