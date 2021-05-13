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
	BUTTON->AddButton("start_button", Vec2(600, 250), "title");
	BUTTON->AddButton("guide_button", Vec2(600, 650), "title");
	BUTTON->AddButton("adven_button", Vec2(600, 1050), "title");
	BUTTON->AddButton("develop_button", Vec2(600, 1450), "title");
	BUTTON->AddButton("quit_button", Vec2(600, 1850), "title");

	guideUI = false;
}

void cTitleScene::Update()
{
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("start_button"))
		{
			SCENE->ChangeScene("cIntroScene");
		}
		else if (MOUSE->Collider("guide_button"))
		{
			if (!guideUI)
				guideUI = true;
		}
		else if (MOUSE->Collider("adven_button"))
		{

		}
		else if (MOUSE->Collider("develop_button"))
		{

		}
		else if (MOUSE->Collider("quit_button"))
		{

		}
	}
}

void cTitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(IMAGE->FindImage("Logo"), { WINSIZEX / 2, 600 }, 0.5);
	RENDER->CenterRender(IMAGE->FindImage("pattern"), { 500, 1000 });

	for (auto iter : BUTTON->m_buttons)
	{
		if (iter->m_tag == "title")
			iter->Render();
	}

	RENDER->CenterRender(IMAGE->FindImage("start_note"), { 170, 250 });
	RENDER->CenterRender(IMAGE->FindImage("guide_note"), { 170, 650 });
	RENDER->CenterRender(IMAGE->FindImage("adven_note"), { 170, 1050 });
	RENDER->CenterRender(IMAGE->FindImage("develop_note"), { 170, 1450 });
	RENDER->CenterRender(IMAGE->FindImage("quit_note"), { 170, 1850 });

	if (guideUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("guide_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	}

	RENDER->CenterRender(IMAGE->FindImage("player"),
		{ float(MOUSE->mousePos.x * 2.1),
		 float(MOUSE->mousePos.y * 2.1)
		}, 0.2);
}

void cTitleScene::UIRender()
{

}

void cTitleScene::Release()
{
	for (auto iter : BUTTON->m_buttons) SAFE_DELETE(iter);
	BUTTON->m_buttons.clear();
}
