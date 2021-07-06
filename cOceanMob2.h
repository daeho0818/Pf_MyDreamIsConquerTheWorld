#pragma once
class cOceanMob2
	:public cMob
{
public:
	cOceanMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cOceanMob2();

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

