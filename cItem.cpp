#include "DXUT.h"
#include "cItem.h"

cItem::cItem(Vec2 pos)
	:m_pos(pos)
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
	RENDER->CenterRender(m_image, m_pos);
}