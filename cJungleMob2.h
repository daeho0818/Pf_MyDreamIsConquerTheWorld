#pragma once
class cJungleMob2
	:public cMob
{
public:
	cJungleMob2(Vec2 pos);
	~cJungleMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

