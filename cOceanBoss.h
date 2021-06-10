#pragma once
#include "cMob.h"
class cOceanBoss
	:public cMob
{
public:
	cOceanBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cOceanBoss();

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1;

	vector<cBullet*>& m_bullets;

	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};