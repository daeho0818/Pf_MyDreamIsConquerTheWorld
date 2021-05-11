#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
}

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	m_buttons.push_back(new cButton(IMAGE->FindImage("Start"), { 1000, 450 }, "none"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("hStart"), { 1000, 450 }, "Start"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("HowTo"), { 1000, 550 }, "none"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("hHowTo"), { 1000, 550 }, "HowTo"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("goIntro"), { 1000, 650 }, "none"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("hgoIntro"), { 1000, 650 }, "Intro"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("End"), { 1000, 750 }, "none"));
	m_buttons.push_back(new cButton(IMAGE->FindImage("hEnd"), { 1000, 750 }, "End"));
}

void cTitleScene::Update()
{
	if (INPUT->KeyDown(VK_DOWN))
	{
		if (!htUI)
			if (select < 4)
				select++;
	}
	else if (INPUT->KeyDown(VK_UP))
	{
		if (!htUI)
			if (select > 1)
				select--;
	}

	if (INPUT->KeyDown(VK_SPACE))
	{
		switch (select)
		{
		case 1:
			SCENE->ChangeScene("cIngameScene");
			break;
		case 2:
			htUI = !htUI;
			break;
		case 3:
			SCENE->ChangeScene("cIntroScene");
			break;
		case 4:
			PostQuitMessage(0);
			break;
		}
	}
}

void cTitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), { WINSIZEX / 2, WINSIZEY / 2 }, 0.5);
	if (htUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("HowToUI"), { WINSIZEX / 2, WINSIZEY / 2 });
	}
	RENDER->CenterRender(IMAGE->FindImage("player"), { (float)MOUSE->mousePos.x, (float)MOUSE->mousePos.y }, 0.2);
}

void cTitleScene::UIRender()
{
	UI->CenterRender(IMAGE->FindImage("Logo"), { WINSIZEX / 3 + 100, 150 });
	UI->CenterRender(IMAGE->FindImage("pattern"), {150, 0});
	UI->CenterRender(IMAGE->FindImage("start_note"), {70, 100});
	if (!htUI)
	{
		for (auto iter : m_buttons)
		{
			if (iter->m_tag == "none")
				iter->UIRender();
			if (iter->m_tag == "Start" && select == 1)
			{
				iter->UIRender();
			}
			if (iter->m_tag == "HowTo" && select == 2)
			{
				iter->UIRender();
			}
			if (iter->m_tag == "Intro" && select == 3)
			{
				iter->UIRender();
			}
			if (iter->m_tag == "End" && select == 4)
			{
				iter->UIRender();
			}
		}
	}
}

void cTitleScene::Release()
{
	for (auto iter : m_buttons) SAFE_DELETE(iter);
	m_buttons.clear();
}
