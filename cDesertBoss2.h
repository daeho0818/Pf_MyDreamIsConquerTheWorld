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

	bool isStop;
	bool pattern1 = false;
	bool pattern2 = true;
	bool pattern3 = false;

	vector<cBullet*>& m_bullets;

	cTimer* t_Pattern2 = nullptr;
	cTimer* t_Pattern3 = nullptr;

	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};