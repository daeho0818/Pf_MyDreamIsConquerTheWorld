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
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	bool isStop;
	bool pattern1 = true;

	int dirIndex = 0;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};