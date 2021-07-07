#pragma once
class cItem
{
public:
	cItem(Vec2 pos, float size);
	virtual ~cItem();

	string itemName;
	Vec2 m_pos;
	cTexture* m_image;
	bool isDestroy = false;
	float m_size;

	void Update();
	void Render();
};

