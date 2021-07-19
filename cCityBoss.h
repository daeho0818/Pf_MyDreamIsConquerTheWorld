#pragma once
#include "cMob.h"
class cCityBoss
	:public cMob
{
public:
	cCityBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cCityBoss();

	int p1Count = 0;

	vector<cBullet*>& m_bullets;

	cBullet* bullets[4] = { nullptr, };

	void CircleBullet(float interval, Vec2 pos = Vec2());

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};