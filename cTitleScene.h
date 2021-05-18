#pragma once
#include "cPlayer.h"
#include "cScene.h"
#include "cButton.h"

class cTitleScene
	:public cScene
{
public:
	cTitleScene();
	~cTitleScene();

	int select = 1;

	bool guideUI = false;
	bool advenUI = false;
	bool buttonsMoved = false;
	bool movedEnd = true;

	bool move[7] = { false, };
	float speed = 0;

	float temp = 0;

	int count = 0;

	cTimer* t_Delay = nullptr;

	Vec2 logoPos = { WINSIZEX / 2, -500 };

	string arrowKey = "Arrow";

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;
};