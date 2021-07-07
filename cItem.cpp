#include "DXUT.h"
#include "cItem.h"

cItem::cItem(Vec2 pos, float size)
	:m_pos(pos), m_size(size)
{
}

cItem::~cItem()
{
}

void cItem::Update()
{
}

void cItem::Render()
{
	RENDER->CenterRender(m_image, m_pos, m_size);
}