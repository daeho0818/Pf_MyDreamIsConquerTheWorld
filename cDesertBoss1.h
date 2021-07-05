#pragma once
#include "cMob.h"
class cDesertBoss1
	:public cMob
{
public:
	cDesertBoss1(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cDesertBoss1();

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};