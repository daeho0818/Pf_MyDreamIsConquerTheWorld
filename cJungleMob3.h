#pragma once
class cJungleMob3
	:public cMob
{
public:
	cJungleMob3(Vec2 pos);
	~cJungleMob3();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};

