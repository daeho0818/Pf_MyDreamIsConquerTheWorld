#pragma once
class cChurchMob2
	:public cMob
{
public:
	cChurchMob2(Vec2 pos, vector<cBullet*>& bullets, float size = 1);
	~cChurchMob2();
	
	vector<cBullet*>& m_bullets;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

