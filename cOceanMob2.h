#pragma once
class cOceanMob2
	:public cMob
{
public:
	cOceanMob2(Vec2 pos);
	~cOceanMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

