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

	if (high_BG != nullptr)
	{
		RENDER->CenterRender(high_BG, Vec2(WINSIZEX / 2, WINSIZEY / 2));
	}
}
