#pragma once
class cDesertMob1
	:public cMob
{
public:
	cDesertMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cDesertMob1();

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

