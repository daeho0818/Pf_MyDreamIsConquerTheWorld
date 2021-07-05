#include "DXUT.h"
#include "cButtonManager.h"

cButtonManager::cButtonManager()
{
}

cButtonManager::~cButtonManager()
{
	for (auto iter : m_buttons) SAFE_DELETE(iter);

	m_buttons.clear();

	buttonPos.clear();

	buttonRects.clear();
}

void cButtonManager::AddButton(string key, Vec2 pos, float size)
{
	m_buttons.push_back(new cButton(IMAGE->FindImage(key), pos, size));
	buttonPos.insert(make_pair(key, pos));
	RECT startButtonRect = {
		buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width * size / 2),
		buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height * size / 2),
		buttonPos.find(key)->second.x + (IMAGE->FindImage(key)->info.Width * size / 2),
		buttonPos.find(key)->second.y + (IMAGE->FindImage(key)->info.Height * size / 2)
	};
	buttonRects.insert(make_pair(key, startButtonRect));
}

void cButtonManager::ChangeBtnInfo(string key, Vec2 pos, float size)
{
	auto find = buttonPos.find(key);
	find->second = pos;
	RECT startButtonRect = {
	buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2) * size,
	buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2) * size,
	float(IMAGE->FindImage(key)->info.Width + buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2)),
	float(IMAGE->FindImage(key)->info.Height + buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2))
	};
	auto r_find = buttonRects.find(key);
	r_find->second = startButtonRect;
}