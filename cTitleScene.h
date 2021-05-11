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
	bool htUI = false;

	vector<cButton*> m_buttons;
	map<string, Vec2> buttonPos;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Release() override;

};