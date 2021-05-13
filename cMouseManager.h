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
	// 사용 방법 : 버튼의 RECT 변수 넘겨주고 버튼의 Vec2 위치, 버튼의 이미지 넘겨주게 되면 충돌 여부 반환
	bool CBColl(RECT rc, Vec2 pos, cTexture* ptr);

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
