#pragma once
#include "cMob.h"
class cIceBoss
	:public cMob
{
public:
	cIceBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cIceBoss();

	int p1Count;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};