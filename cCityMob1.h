#pragma once
class cCityMob1
	:public cMob
{
public:
	cCityMob1(Vec2 pos, vector<cBullet*>& m_bullets, float size = 1);
	~cCityMob1();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

