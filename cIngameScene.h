#pragma once
#include "cPlayer.h"
#include "cScene.h"
#include "cItemAdmin.h"
#include "cCollision.h"
#include "cMobAdmin.h"
#include "cBulletAdmin.h"
class cIngameScene
	:public cScene
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
	cTimer* AS = nullptr;
	cTimer* t_Delay = nullptr;
	cTimer* Expl[5] = { nullptr, };
};