#include "DXUT.h"
#include "cHeal.h"

cHeal::cHeal(Vec2 pos)
	:cItem(pos)
{
	itemName = "Heal";
	m_image = IMAGE->FindImage("Hp+");
}

cHeal::~cHeal()
{
}