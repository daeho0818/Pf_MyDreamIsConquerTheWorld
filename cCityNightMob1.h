#pragma once
class cCityNightMob1
	:public cMob
{
public:
	cCityNightMob1(Vec2 pos);
	~cCityNightMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

