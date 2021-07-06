#pragma once
class cChurchMob1
	:public cMob
{
public:
	cChurchMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cChurchMob1();

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	vector<cBullet*>& m_bullets;
};

