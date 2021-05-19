#include "DXUT.h"
#include "cButtonManager.h"

cButtonManager::cButtonManager()
{
	SCENE->curScene = "cIceScene";
}

cButtonManager::~cButtonManager()
{
	for (auto iter : m_buttons) SAFE_DELETE(iter);
	m_buttons.clear();
	buttonPos.clear();
	buttonRects.clear();
}

void cButtonManager::AddButton(string key, Vec2 pos, string tag)
{
	float size = 0, min = 0;
	if (tag == "titleB" || tag == "advenB")
	{
		size = 0.6;
	}
	else if (tag == "guideB" || "ingameB" || "stopB")
		size = 1;
	else if (tag == "worldmapB")
	{
		size = 0.6;
		min = 300;
	}
	else if (tag == "X")
	{
		size = 0.6;
	}
	else if (tag == "arrowB")
		size = 1.5;
	else if (tag == "endSceneB")
	{
		size = 0.8;
	}
	m_buttons.push_back(new cButton(IMAGE->FindImage(key), pos, tag, size));
	buttonPos.insert(make_pair(key, pos));
	RECT startButtonRect = {
		buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width * size) / 2,
		buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height * size) / 2,
		buttonPos.find(key)->second.x + (IMAGE->FindImage(key)->info.Width * size) / 2 - min,
		buttonPos.find(key)->second.y + (IMAGE->FindImage(key)->info.Height * size) / 2
	};
	buttonRects.insert(make_pair(key, startButtonRect));
}

void cButtonManager::ChangeBtnInfo(string key, Vec2 pos, string tag)
{
	float size = 0; float min = 0;
	if (tag == "titleB" || tag == "advenB")
	{
		size = 0.6;
		min = 200;
	}
	else if (tag == "guideB" || "ingameB" || "stopB")
		size = 1;
	else if (tag == "worldmapB")
	{
		size = 0.6;
		min = 1000;
	}
	else if (tag == "X")
	{
		size = 0.6;
	}
	else if (tag == "arrowB")
		size = 1.5;
	else if (tag == "endSceneB")
	{
		size = 0.8;
	}

	auto find = buttonPos.find(key);
	find->second = pos;
	RECT startButtonRect = {
	buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2) * size,
	buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2) * size,
	float(IMAGE->FindImage(key)->info.Width + buttonPos.find(key)->second.x - (IMAGE->FindImage(key)->info.Width / 2)) - min,
	float(IMAGE->FindImage(key)->info.Height + buttonPos.find(key)->second.y - (IMAGE->FindImage(key)->info.Height / 2))
	};
	auto r_find = buttonRects.find(key);
	r_find->second = startButtonRect;
}