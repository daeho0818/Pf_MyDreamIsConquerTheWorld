#pragma once
class cIceMob1
	:public cMob
{
public:
	cIceMob1(Vec2 pos, vector<cBullet*>& bullets);
	~cIceMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

