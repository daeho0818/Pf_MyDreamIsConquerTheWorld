#include "DXUT.h"
#include "cSpeed.h"

cSpeed::cSpeed(Vec2 pos, float size)
	:cItem(pos, size)
{
	itemName = "Speed";
	m_image = IMAGE->FindImage("Speed+");
}

cSpeed::~cSpeed()
{
}
