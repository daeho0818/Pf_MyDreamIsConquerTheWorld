#pragma once
class cCityMob2
	:public cMob
{
public:
	cCityMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cCityMob2();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

