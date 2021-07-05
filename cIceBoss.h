#pragma once
#include "cMob.h"
class cIceBoss
	:public cMob
{
public:
	cIceBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cIceBoss();

	int p1Count;

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	cTimer* t_Pattern1 = nullptr;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};