#include "DXUT.h"
#include "cButtonManager.h"

cButtonManager::cButtonManager()
{
}

cButtonManager::~cButtonManager()
{
}

void cButtonManager::AddButton(string key, Vec2 pos, string tag)
{
	float size = 0;
	if (tag == "titleB" || tag == "advenB")
		size = 0.6;
	else if (tag == "guideB")
		size = 1;
	m_buttons.push_back(new cButton(IMAGE->FindImage(key), pos, tag, size));
	buttonPos.insert(make_pair(key, pos));
	RECT startButtonRect = {
		buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2) * size,
		buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2) * size,
		float(IMAGE->FindImage(key)->info.Width + buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2)),
		float(IMAGE->FindImage(key)->info.Height + buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2))
	};
	buttonRects.insert(make_pair(key, startButtonRect));
}
