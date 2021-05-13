#pragma once
#include "cMob.h"
class cBoss
	:public cMob
{
public:
	cBoss(Vec2 pos, vector<cBullet*>& bullet);
	~cBoss();

	float dir_x = 1;
	float dir_y = 1;
	bool isStop;
	vector<cBullet*>& m_bullets;
	cTimer* t_Pattern1 = nullptr;

	string ChkOut();
	void CircleBullet();

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};