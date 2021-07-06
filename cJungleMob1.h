#pragma once
class cJungleMob1
	:public cMob
{
public:
	cJungleMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cJungleMob1();

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

