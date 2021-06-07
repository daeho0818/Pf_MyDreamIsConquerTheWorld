#pragma once
#include "singleton.h"
class cMouseManager
	:public singleton<cMouseManager>
{
public:
	cMouseManager();
	~cMouseManager();

	// Image�� key�� �Ѱ��ָ� �浹 ���� ��ȯ
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
