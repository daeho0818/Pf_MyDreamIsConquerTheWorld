#pragma once
#include "cMob.h"
class cDesertBoss2
	:public cMob
{
public:
	cDesertBoss2(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cDesertBoss2();

	int p1Count = 0;
	int p2Count = 0;
	int p3Count = 0;

	vector<cBullet*>& m_bullets;

	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};