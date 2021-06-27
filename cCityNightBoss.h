#pragma once
#include "cMob.h"
class cCityNightBoss
	:public cMob
{
public:
	cCityNightBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cCityNightBoss();


	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	float dir_x = 1;
	float dir_y = 1;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};