#include "DXUT.h"
#include "cInvincibility.h"

cInvincibility::cInvincibility(Vec2 pos)
	:cItem(pos)
{
	itemName = "Invincibility";
	m_image = IMAGE->FindImage("Invincibility");
}

cInvincibility::~cInvincibility()
{
}
