#pragma once
class cMob abstract
{
public:
	cMob(Vec2 pos) : m_pos(pos) {}
	virtual ~cMob() { SAFE_DELETE(t_Pattern1); }

	Vec2 m_pos;
	Vec2 spawnPos;

	float m_hp;
	float m_damage = 1;
	float m_size;

	int p1Count = 0;
	int index = 0;

	bool isDestroy = false;

	string mobType;
	string mobName;
	
	cTimer* m_Ani = nullptr;
	cTimer* t_Pattern1 = nullptr;

	vector<cTexture*> m_image;

	virtual void Update() = 0;
	virtual void Render() = 0;

	string ChkOut();
};