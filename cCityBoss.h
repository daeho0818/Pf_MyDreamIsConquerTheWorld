#pragma once
#include "cMob.h"
class cCityBoss
	:public cMob
{
public:
	cCityBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cCityBoss();

	int p1Count = 0;

	float dir_x = 1;
	float dir_y = 1;
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	bool isStop;
	bool pattern1;

	vector<cBullet*>& m_bullets;

	void CircleBullet(float interval, bool random = false);

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};