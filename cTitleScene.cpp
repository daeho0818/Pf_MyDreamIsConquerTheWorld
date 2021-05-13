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
	BUTTON->AddButton("start_button", Vec2(600, 250), "titleB");
	BUTTON->AddButton("guide_button", Vec2(600, 650), "titleB");
	BUTTON->AddButton("adven_button", Vec2(600, 1050), "titleB");
	BUTTON->AddButton("develop_button", Vec2(600, 1450), "titleB");
	BUTTON->AddButton("quit_button", Vec2(600, 1850), "titleB");

	BUTTON->AddButton("guide_close", Vec2(3000, WINSIZEY / 2 - 1000), "guideB");
	BUTTON->AddButton("adven_Back", Vec2(660, WINSIZEY / 2 - 670), "advenB");
	guideUI = false;
}

void cTitleScene::Update()
{
	if (guideUI) if (INPUT->KeyDown(VK_ESCAPE)) guideUI = false;
	if (advenUI) if (INPUT->KeyDown(VK_ESCAPE)) advenUI = false;
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("start_button"))
		{
			if (!guideUI && !advenUI)
				SCENE->ChangeScene("cIntroScene");
		}
		else if (MOUSE->Collider("guide_button"))
		{
			if (!guideUI && !advenUI)
				guideUI = true;
		}
		else if (MOUSE->Collider("adven_button"))
		{
			if (!advenUI && !guideUI)
				advenUI = true;
		}
		else if (MOUSE->Collider("develop_button"))
		{
		}
		else if (MOUSE->Collider("quit_button"))
		{
		}
		else if (MOUSE->Collider("guide_close"))
		{
			if (guideUI)
				guideUI = false;
		}
		else if (MOUSE->Collider("adven_Back"))
		{
			if (advenUI)
				advenUI = false;
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
		if (iter->m_tag == "titleB")
			iter->Render();
	}

	RENDER->CenterRender(IMAGE->FindImage("start_note"), { 170, 250 });
	RENDER->CenterRender(IMAGE->FindImage("guide_note"), { 170, 650 });
	RENDER->CenterRender(IMAGE->FindImage("adven_note"), { 170, 1050 });
	RENDER->CenterRender(IMAGE->FindImage("develop_note"), { 170, 1450 });
	RENDER->CenterRender(IMAGE->FindImage("quit_note"), { 170, 1850 });

	if (guideUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("guide_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_text1"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_close"), Vec2(3000, WINSIZEY / 2 - 1000));
	}
	else if (advenUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("adven_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_BGRect"), Vec2(WINSIZEX / 2, WINSIZEY / 2) , 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_ContentBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 430), 0.6);
		RENDER->CenterRender(IMAGE->FindImage("adven_ContentRect"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 430), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_ContentBG"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 430) * 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_ContentRect"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 430) * 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_Back"), Vec2(3000, WINSIZEY / 2 - 900), 0.8);

		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPerBG"), Vec2(500, WINSIZEY - 350), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CircleDown"), Vec2(500, WINSIZEY - 350), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CircleUp"), Vec2(500, WINSIZEY - 350), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPer"), Vec2(500, WINSIZEY - 350), 0.5);
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
