#pragma once
class cCityNightMob2
	:public cMob
{
public:
	cCityNightMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cCityNightMob2();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

