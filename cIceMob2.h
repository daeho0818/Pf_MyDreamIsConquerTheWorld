#pragma once
class cIceMob2
	:public cMob
{
public:
	cIceMob2(Vec2 pos);
	~cIceMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};

