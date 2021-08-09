#pragma once
class cMob abstract
{
public:
	cMob(Vec2 pos, float size) : m_pos(pos), m_size(size) { }
	virtual ~cMob() { SAFE_DELETE(t_Pattern1); }

	Vec2 m_pos;
	Vec2 spawnPos;

	float m_hp;
	float m_damage = 1;
	float m_size;

	float dir_x = 1;
	float dir_y = 1;

	int p1Count = 0;
	int index = 0;
	int speed;

	bool isDestroy = false;
	bool isStop;
	bool pattern1;
	bool pattern2;
	bool pattern3;

	string mobType;
	string mobName;

	cTimer* m_Ani = nullptr;
	cTimer* t_Pattern1 = nullptr;
	cTimer* t_Pattern2 = nullptr;
	cTimer* t_Pattern3 = nullptr;

	vector<cTexture*> m_image;

	virtual void Update() = 0;
	virtual void Render() = 0;

	string ChkOut();
};