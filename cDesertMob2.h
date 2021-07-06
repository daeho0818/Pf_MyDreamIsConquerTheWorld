#pragma once
class cDesertMob2
	:public cMob
{
public:
	cDesertMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cDesertMob2();
	
	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

