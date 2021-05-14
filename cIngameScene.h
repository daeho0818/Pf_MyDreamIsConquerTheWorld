#pragma once
#include "cPlayer.h"
#include "cScene.h"
#include "cItemAdmin.h"
#include "cCollision.h"
#include "cMobAdmin.h"
#include "cBulletAdmin.h"
#include "cParentScene.h"
class cIngameScene
	:public cScene, cParentScene
{
public:
	cIngameScene();
	~cIngameScene();

	cPlayer* player = nullptr;
	cMobAdmin* mob = nullptr;
	cItemAdmin* item = nullptr;
	cCollision* coll = nullptr;
	cBulletAdmin* bullet = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void PrintStageTxt();
	void Explosion();
	bool left , right;
	float pos_x;
	bool isClearScene = false;
	bool delay = false;

	int textCount = 1;
	cTimer* AS = nullptr;
	cTimer* t_Delay = nullptr;
	cTimer* t_TextAni = nullptr;
	cTimer* Expl[5] = { nullptr, };

	Vec2 textPos[4][3] = {
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}},
		{{-100, (float)WINSIZEY / 2} ,{(float)WINSIZEX / 2, (float)WINSIZEY / 2}, {(float)WINSIZEX + 500, (float)WINSIZEY / 2}}
	};
	// cParentScene을(를) 통해 상속됨
};