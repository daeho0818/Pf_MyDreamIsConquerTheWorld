#pragma once
class cCityMob2
	:public cMob
{
public:
	cCityMob2(Vec2 pos, vector<cBullet*>& bullets);
	~cCityMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

