#pragma once
#include "singleton.h"
class cInputManager
	:public singleton<cInputManager>
{
	bool nowkey[256];
	bool oldkey[256];
public:
	cInputManager();
	~cInputManager();

	void Update();
	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);

	void SetMousePos();
};

#define INPUT cInputManager::GetInstance()