#pragma once
class cButton
{
public:
	cButton(cTexture* ptr, Vec2 pos, string tag);
	~cButton();

	cTexture* m_ptr;
	Vec2 m_pos;
	string m_tag;

	void Init();
	void UIRender();
};

