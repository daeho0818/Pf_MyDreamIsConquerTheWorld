#pragma once
#include "cMob.h"
class cCityBoss
	:public cMob
{
public:
	cCityBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cCityBoss();

	bool moveToTarget = false;

	Vec2 playerPos;

private:
	int p1Count = 0;
	int delayCount = 3;

	vector<cBullet*>& m_bullets;

	Vec2 beforePos;
	Vec2 targetPos;

	cBullet* bullets[4] = { nullptr, };

	cTimer* t_ReturnDelay = nullptr;

	void CircleBullet(float interval, Vec2 pos = Vec2());

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};