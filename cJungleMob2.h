#pragma once
class cJungleMob2
	:public cMob
{
public:
	cJungleMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cJungleMob2();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

