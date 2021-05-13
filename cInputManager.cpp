#include "DXUT.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
}

cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
	SetMousePos();
	for (int i = 0; i < 256; i++) oldkey[i] = nowkey[i];
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i)) nowkey[i] = true;
		else nowkey[i] = false;
	}
}

bool cInputManager::KeyPress(int key)
{
	return nowkey[key] && oldkey[key];
}

bool cInputManager::KeyDown(int key)
{
	return nowkey[key] && !oldkey[key];
}

bool cInputManager::KeyUp(int key)
{
	return !nowkey[key] && oldkey[key];
}

void cInputManager::SetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	MOUSE->mousePos = pt;
}
