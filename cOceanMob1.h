#pragma once
class cOceanMob1
	:public cMob
{
public:
	cOceanMob1(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cOceanMob1();
	
	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

