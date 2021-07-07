#include "DXUT.h"
#include "cHeal.h"

cHeal::cHeal(Vec2 pos, float size)
	:cItem(pos, size)
{
	itemName = "Heal";
	m_image = IMAGE->FindImage("Hp+");
}

cHeal::~cHeal()
{
}