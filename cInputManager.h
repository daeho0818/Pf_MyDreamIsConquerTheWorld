#pragma once
#include "singleton.h"
class cInputManager
	:public singleton<cInputManager>
{
	bool nowkey[256];
	bool oldkey[256];

	void SetMousePos();
public:
	cInputManager();
	~cInputManager();

	void Update();
	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);
};

#define INPUT cInputManager::GetInstance()