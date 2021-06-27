#pragma once
class cButton
{
public:
	cButton(cTexture* ptr, Vec2 pos, float size);
	~cButton();

	cTexture* m_ptr;
	Vec2 m_pos;
	float m_size;

	void Init();
	void Render();
	void UIRender();
};

