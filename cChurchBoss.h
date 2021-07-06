#pragma once
#include "cMob.h"
class cChurchBoss
	:public cMob
{
public:
	cChurchBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cChurchBoss();

	int p1Count = 0;
	int p2Count = 0;
	int p3Count = 0;

	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};