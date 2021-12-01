#pragma once
#include "cPlayer.h"
#include "cMobAdmin.h"
#include "cItemAdmin.h"
#include "cBulletAdmin.h"
#include "cCollision.h"
class cParentScene
{
public:
	cParentScene();
	~cParentScene();

	virtual void Init(string curScene);
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();

	void PlayerDead();

private:
	int score;
	int alphaColor = 255;
	int effectCount = 0;
	int hp;

	bool waitToStart;
	bool clear[7];
	bool over[4];
	bool textRender[7];
	bool isFadeOut;
	bool once;

	float operValue;

	cTimer* t_TextAni = nullptr;
	cTimer* t_Timer = nullptr;
	cTimer* t_Clear = nullptr;
	cTimer* t_Over = nullptr;
	cTimer* t_Delay = nullptr;
	cTimer* t_WaitToStart = nullptr;
	cTimer* t_TimeFade = nullptr;
	cTimer* t_CamMove = nullptr;
	cTimer* t_EffectDelay = nullptr;

	Vec2 textsPos[7];
	Vec2 bossPos;
	Vec2 playerPos;

	void SceneUpdate();
	void SceneRender();
	void SceneUIRender();

public:
	int textCount;
	int timer;
	int CFCount;
	int delayCount;

	float speed;

	bool isStart;
	bool isStop;
	bool isdead;
	bool isClear;
	bool isFail;
	bool isClearEnd;
	bool isFailEnd;
	bool delay;


	cTexture* t_BG = nullptr;

	cPlayer* player = nullptr;

	cMobAdmin* mob = nullptr;

	cItemAdmin* item = nullptr;

	cBulletAdmin* bullet = nullptr;

	cCollision* coll = nullptr;

	Vec2 ui_operation_position;

	cTexture* ui_bg_image;
	cTexture* high_ui_image;
};

