#pragma once
class cCityMob1
	:public cMob
{
public:
	cCityMob1(Vec2 pos);
	~cCityMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};

