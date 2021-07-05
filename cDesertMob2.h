#pragma once
class cDesertMob2
	:public cMob
{
public:
	cDesertMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cDesertMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

