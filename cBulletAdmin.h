#pragma once
#include "cBullet.h"
class cBulletAdmin
{
public:
	vector<cBullet*> m_bullets;

	cBulletAdmin();
	~cBulletAdmin();
	
	void Update();
	void Render();
	void IsOut();
	void IsDestroy();
};

