#pragma once
class cReflexBullet
	:public cBullet
{
public:
	cReflexBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, string bulletType, float damage, float size, float speed, bool dead = false);
	~cReflexBullet();

	bool dead;
	float m_speed;

	cTimer* t_Dead = nullptr;

	// cBullet��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};