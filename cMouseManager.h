#pragma once
#include "singleton.h"
class cMouseManager
	:public singleton<cMouseManager>
{
public:
	cMouseManager();
	~cMouseManager();

	// Image의 key값 넘겨주면 충돌 여부 반환
	bool Collider(string key, Vec2 pos = Vec2(0, 0));

	bool CBColl(RECT rc, Vec2 pos = Vec2(0, 0));

	void Update();
	void Render();
	void LButtonDown();
	void LButtonUp();

	bool LButtonClick(string key);

	bool render = false; Vec2 temp;
	bool lUp = false, lDown = false, rUp = false, rDown = false;
	bool lStay = false, rStay = false;

	Vec2 mousePos;
	Vec2 lDownPos = { 0, 0 }, lUpPos = { 0, 0 };

	cTimer* AS = nullptr;
};
#define MOUSE cMouseManager::GetInstance()