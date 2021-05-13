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

bool cMouseManager::Collider(string key)
{
	return CBColl(BUTTON->buttonRects.find(key)->second, BUTTON->buttonPos.find(key)->second, IMAGE->FindImage(key));
}

bool cMouseManager::CBColl(RECT rc, Vec2 pos, cTexture* ptr)
{
	pos.x -= ptr->info.Width / 2;
	pos.y -= ptr->info.Height / 2;
	if (mousePos.x * 2.1 >= (float(rc.left + pos.x)) && mousePos.x * 2.1 <= (float(rc.right + pos.x)) &&
		mousePos.y * 2.1 >= (float(rc.top + pos.y)) && mousePos.y * 2.1 <= (float(rc.bottom + pos.y))) return true;
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
