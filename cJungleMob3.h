#pragma once
class cJungleMob3
	:public cMob
{
public:
	cJungleMob3(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cJungleMob3();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

