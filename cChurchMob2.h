#pragma once
class cChurchMob2
	:public cMob
{
public:
	cChurchMob2(Vec2 pos);
	~cChurchMob2();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};

