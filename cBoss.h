#pragma once
#include "cMob.h"
class cBoss
	:public cMob
{
public:
	cBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cBoss();

	int count = 0;

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1 = false;
	bool pattern2 = true;

	vector<cBullet*>& m_bullets;

	cTimer* t_Pattern1 = nullptr;
	cTimer* t_Pattern2 = nullptr;

	string ChkOut();
	void CircleBullet();

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};