#pragma once
#include "singleton.h"
class cButtonManager
	:public singleton<cButtonManager>
{
public:
	cButtonManager();
	~cButtonManager();

	vector<cButton*> m_buttons;
	map<string, RECT> buttonRects;
	map<string, Vec2> buttonPos;

	void AddButton(string key, Vec2 pos, string tag);
};
#define BUTTON cButtonManager::GetInstance()