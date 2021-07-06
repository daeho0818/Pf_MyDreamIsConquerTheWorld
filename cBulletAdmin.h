#pragma once
#include "cBullet.h"
class cBulletAdmin
{
public:
	vector<cBullet*> m_bullets;

	cBulletAdmin();
	~cBulletAdmin();
	
	float temp = 0;

	void Update();
	void Render();
	void IsOut();
	void IsDestroy();
};

