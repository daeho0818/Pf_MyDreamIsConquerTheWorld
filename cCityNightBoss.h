#pragma once
#include "cMob.h"
class cCityNightBoss
	:public cMob
{
public:
	cCityNightBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cCityNightBoss();

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	vector<cBullet*>& m_bullets;
};