#pragma once
class cIceMob2
	:public cMob
{
public:
	cIceMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cIceMob2();

	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

