#include "DXUT.h"
#include "cInvincibility.h"

cInvincibility::cInvincibility(Vec2 pos, float size)
	:cItem(pos, size)
{
	itemName = "Invincibility";
	m_image = IMAGE->FindImage("Invincibility");
}

cInvincibility::~cInvincibility()
{
}
