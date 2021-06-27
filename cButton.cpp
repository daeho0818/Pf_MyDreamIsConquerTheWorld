#include "DXUT.h"
#include "cButton.h"

cButton::cButton(cTexture* ptr, Vec2 pos, float size)
	:m_ptr(ptr), m_pos(pos), m_size(size)
{
	Init();
}

cButton::~cButton()
{
}

void cButton::Init()
{
}

void cButton::Render()
{
	RENDER->CenterRender(m_ptr, m_pos, m_size);
}

void cButton::UIRender()
{
}
