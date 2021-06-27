#pragma once
class cMBullet
	:public cBullet
{
public:
	cMBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, float damage, float size = 10, float speed = 700);
	~cMBullet();
	float m_speed;

	virtual void Update() override;
	virtual void Render() override;
};

