#pragma once
class cIceMob1
	:public cMob
{
public:
	cIceMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cIceMob1();

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

