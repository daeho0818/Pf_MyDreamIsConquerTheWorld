#pragma once
class cItem
{
public:
	cItem(Vec2 pos);
	virtual ~cItem();

	string itemName;
	Vec2 m_pos;
	cTexture* m_image;
	bool isDestroy = false;
	float m_size = 30;

	void Update();
	void Render();
};

