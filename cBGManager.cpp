#include "DXUT.h"
#include "cBGManager.h"

cBGManager::cBGManager()
{
}

cBGManager::~cBGManager()
{
}

void cBGManager::Render()
{
	RENDER->CenterRender(ptr[1], Vec2(WINSIZEX / 2, WINSIZEY / 2));
	RENDER->CenterRender(ptr[0], Vec2(WINSIZEX / 2, WINSIZEY / 2));
}
