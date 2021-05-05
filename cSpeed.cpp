#include "DXUT.h"
#include "cSpeed.h"

cSpeed::cSpeed(Vec2 pos)
	:cItem(pos)
{
	itemName = "Speed";
	m_image = IMAGE->FindImage("Speed+");
}

cSpeed::~cSpeed()
{
}
