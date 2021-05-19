#pragma once
class cDesertMob1
	:public cMob
{
public:
	cDesertMob1(Vec2 pos);
	~cDesertMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};

