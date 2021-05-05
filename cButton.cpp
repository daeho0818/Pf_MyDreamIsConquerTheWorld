#include "DXUT.h"
#include "cButton.h"

cButton::cButton(cTexture* ptr, Vec2 pos, string tag)
	:m_ptr(ptr), m_pos(pos), m_tag(tag)
{
	Init();
}

cButton::~cButton()
{
}

void cButton::Init()
{
}

void cButton::UIRender()
{
	UI->CenterRender(m_ptr, m_pos);
}
