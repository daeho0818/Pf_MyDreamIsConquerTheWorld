#pragma once
class cMob abstract
{
public:
	cMob(Vec2 pos) : m_pos(pos) {}
	virtual ~cMob() {}

	Vec2 m_pos;
	Vec2 spawnPos;

	float m_hp;
	float m_damage;
	float m_size;

	int index = 0;

	bool isDestroy = false;

	string mobType;
	string mobName;
	
	cTimer* m_Ani = nullptr;

	vector<cTexture*> m_image;

	virtual void Update() = 0;
	virtual void Render() = 0;
};