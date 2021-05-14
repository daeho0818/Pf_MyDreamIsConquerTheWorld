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
	bool left , right;
	float pos_x;

	cTimer* AS = nullptr;
};