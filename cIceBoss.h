#pragma once
#include "cMob.h"
class cIceBoss
	:public cMob
{
public:
	cIceBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cIceBoss();

	int p1Count;

	bool isStop;
	bool pattern1 = true;

	vector<cBullet*>& m_bullets;

	cTimer* t_Pattern1 = nullptr;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};