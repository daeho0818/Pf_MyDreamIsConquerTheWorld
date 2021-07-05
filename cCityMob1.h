#pragma once
class cCityMob1
	:public cMob
{
public:
	cCityMob1(Vec2 pos, vector<cBullet*>& m_bullets, float size = 1);
	~cCityMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

