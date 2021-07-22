#pragma once
class cBullet
{
public:
	Vec2 m_pos;
	Vec2 m_Dir;

	float m_angle;
	float size;
	float m_Damage;

	bool isDestroy = false;

	string bulletType;
	string effectName;

	cTexture* m_image;

	cBullet(Vec2 pos, Vec2 dir, string imgName, string effectName, string bulletType, float size);
	virtual ~cBullet();

	bool IsOutMap();
	virtual void Update() = 0;
	virtual void Render() = 0;
};

