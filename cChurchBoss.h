#pragma once
#include "cMob.h"
class cChurchBoss
	:public cMob
{
public:
	cChurchBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cChurchBoss();

	int p1Count = 0;
	int p2Count = 0;
	int p3Count = 0;

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	cTimer* t_Pattern1 = nullptr;

	string ChkOut();
	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};