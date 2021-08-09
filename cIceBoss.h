#pragma once
#include "cMob.h"
class cIceBoss
	:public cMob
{
public:
	cIceBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cIceBoss();

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<cBullet*>& m_bullets;

	bool dashStart = false;

	void XFire();
};