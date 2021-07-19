#pragma once
#include "cPlayer.h"
class cMobAdmin
{
public:
	cMobAdmin(cPlayer* player, vector<cBullet*>& bullet, string stage);
	~cMobAdmin();

	void Update();
	void Render();
	void UIRender();

	void Animation();

	bool isDestroy;

	Vec2 bossPos;

	vector<cMob*> m_mobs;
	vector<cBullet*>& m_bullets;

private:
	string stage;

	bool repeat;

	cPlayer* m_player;

	cTimer* t_DeadDelay = nullptr;

	void IsDestroy();
};

