#pragma once
class cCityNightMob2
	:public cMob
{
public:
	cCityNightMob2(Vec2 pos);
	~cCityNightMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

