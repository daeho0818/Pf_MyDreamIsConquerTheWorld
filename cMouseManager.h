#pragma once
#include "singleton.h"
class cMouseManager
	:public singleton<cMouseManager>
{
public:
	cMouseManager();
	~cMouseManager();

	// Image의 key값 넘겨주면 충돌 여부 반환
	bool Collider(string key);
	bool CBColl(RECT rc);

	void Update();
	void Render();
	void LButtonDown();
	void LButtonUp();

	bool render = false; Vec2 temp;
	bool lUp = false, lDown = false, rUp = false, rDown = false;
	POINT mousePos;

	cTimer* AS = nullptr;
};

#define MOUSE cMouseManager::GetInstance()
