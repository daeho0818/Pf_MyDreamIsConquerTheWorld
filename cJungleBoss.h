#pragma once
#include "cMob.h"
class cJungleBoss
	:public cMob
{
public:
	cJungleBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cJungleBoss();

	bool isStop;
	bool pattern1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};