#pragma once
class cJungleMob3
	:public cMob
{
public:
	cJungleMob3(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cJungleMob3();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

