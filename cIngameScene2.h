#pragma once
#include "cPlayer.h"
#include "cScene.h"
#include "cMobAdmin.h"
#include "cItemAdmin.h"
#include "cCollision.h"
class cIngameScene2
	:public cScene
{
public:
	cIngameScene2();
	~cIngameScene2();

	cPlayer* player = nullptr;
	cMobAdmin* mob = nullptr;
	cItemAdmin* item = nullptr;
	cCollision* coll = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

	void PrintStageTxt();
	void Explosion();

	bool left, right;
	bool delay;
	float pos_x;
	bool isClearScene = false;
	cTimer* AS = nullptr;
	cTimer* t_Delay = nullptr;
	cTimer* Expl[5] = { nullptr, };
};