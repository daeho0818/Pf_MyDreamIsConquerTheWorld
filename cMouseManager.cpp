#include "DXUT.h"
#include "cMouseManager.h"

cMouseManager::cMouseManager()
{
}

cMouseManager::~cMouseManager()
{
	SAFE_DELETE(AS);
}

void cMouseManager::Update()
{
	if (AS != nullptr) AS->Update();
}

bool cMouseManager::CBColl(RECT rc, Vec2 pos, cTexture* ptr)
{
	pos.x -= ptr->info.Width / 2;
	pos.y -= ptr->info.Height / 2;
	if (mousePos.x >= (rc.left + pos.x) && mousePos.x <= (rc.right + pos.x) &&
		mousePos.y >= (rc.top + pos.y) && mousePos.y <= (rc.bottom + pos.y)) return true;
	return false;
}

void cMouseManager::LButtonDown()
{
	lDown = true;
	AS = new cTimer(0.1, [&]()->void {
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
