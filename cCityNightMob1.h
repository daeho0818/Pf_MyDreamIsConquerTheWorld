#pragma once
class cCityNightMob1
	:public cMob
{
public:
	cCityNightMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cCityNightMob1();
	
	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

