#pragma once
class cButton
{
public:
	cButton(cTexture* ptr, Vec2 pos, string tag, float size = 1);
	~cButton();

	cTexture* m_ptr;
	Vec2 m_pos;
	string m_tag;
	float m_size;

	void Init();
	void Render();
	void UIRender();
};

