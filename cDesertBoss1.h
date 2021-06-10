#pragma once
#include "cMob.h"
class cDesertBoss1
	:public cMob
{
public:
	cDesertBoss1(Vec2 pos, vector<cBullet*>& bullet);
	~cDesertBoss1();


	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};