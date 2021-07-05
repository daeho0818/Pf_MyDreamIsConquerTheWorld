#pragma once
class cIceMob2
	:public cMob
{
public:
	cIceMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cIceMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

