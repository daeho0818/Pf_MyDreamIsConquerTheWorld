#include "DXUT.h"
#include "cEndScene.h"

cEndScene::cEndScene()
{
}

cEndScene::~cEndScene()
{
}

void cEndScene::Init()
{
	BUTTON->AddButton("end_restart", Vec2(WINSIZEX / 2 - ((WINSIZEX / 2) / 2), 2000), "endSceneB");
	BUTTON->AddButton("end_title", Vec2(WINSIZEX / 2, 2000), "endSceneB");
	BUTTON->AddButton("end_worldmap", Vec2(WINSIZEX / 2 + ((WINSIZEX / 2) / 2), 2000), "endSceneB");
}

void cEndScene::Update()
{
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("end_restart"))
		{
			SCENE->ChangeScene(SCENE->curScene);
		}
		if (MOUSE->Collider("end_title"))
		{
			SCENE->ChangeScene("cTitleScene");
		}
		if (MOUSE->Collider("end_worldmap"))
		{
			SCENE->ChangeScene("cSelectStageScene");
		}
		MOUSE->lUp = false;
	}
}

void cEndScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	RENDER->CenterRender(IMAGE->FindImage("end_restart"), Vec2(WINSIZEX / 2 - ((WINSIZEX / 2) / 2), 2000), 0.8);
	RENDER->CenterRender(IMAGE->FindImage("end_title"), Vec2(WINSIZEX / 2, 2000), 0.8);
	RENDER->CenterRender(IMAGE->FindImage("end_worldmap"), Vec2(WINSIZEX / 2 + ((WINSIZEX / 2) / 2), 2000), 0.8);
}

void cEndScene::UIRender()
{
}

void cEndScene::Release()
{
}
