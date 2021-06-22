#include "DXUT.h"
#include "cMouseManager.h"

cMouseManager::cMouseManager()
{
	//ShowCursor(false);
}

cMouseManager::~cMouseManager()
{
	SAFE_DELETE(AS);
}

void cMouseManager::Update()
{
	if (AS != nullptr) AS->Update();
}

void cMouseManager::Render()
{
}

bool cMouseManager::Collider(string key, Vec2 pos)
{
	return CBColl(BUTTON->buttonRects.find(key)->second, pos);
}

bool cMouseManager::CBColl(RECT rc, Vec2 pos)
{
	if (pos == Vec2(0, 0))
	{
		if (mousePos.x * 2.1 >= float(rc.left) && mousePos.x * 2.1 <= float(rc.right) &&
			mousePos.y * 2.1 >= float(rc.top) && mousePos.y * 2.1 <= float(rc.bottom)) return true;
		return false;
	}

	if (pos.x * 2.1 >= float(rc.left) && pos.x * 2.1 <= float(rc.right) &&
		pos.y * 2.1 >= float(rc.top) && pos.y * 2.1 <= float(rc.bottom)) return true;
	return false;
}

void cMouseManager::LButtonDown()
{
	lDown = true;
	AS = new cTimer(0.01, [&]()->void {
		lDown = false;
		AS = nullptr;
		});
}

void cMouseManager::LButtonUp()
{
	lUp = true;
	AS = new cTimer(0.1, [&]()->void {
		lUp = false;
		AS = nullptr;
		});
}
