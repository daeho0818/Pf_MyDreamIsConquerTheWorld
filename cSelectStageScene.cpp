#include "DXUT.h"
#include "cSelectStageScene.h"

cSelectStageScene::cSelectStageScene()
{
}

cSelectStageScene::~cSelectStageScene()
{
}

void cSelectStageScene::Init()
{
	BUTTON->AddButton("guide_close", Vec2(3000, WINSIZEY / 2 - 1000), "guideB");

	BUTTON->AddButton("church_button", Vec2(), "worldmapB");
	BUTTON->AddButton("city_button", Vec2(), "worldmapB");
	BUTTON->AddButton("city(night)_button", Vec2(), "worldmapB");
	BUTTON->AddButton("desert_button", Vec2(), "worldmapB");
	BUTTON->AddButton("ice_button", Vec2(), "worldmapB");
	BUTTON->AddButton("ocean_button", Vec2(), "worldmapB");
	BUTTON->AddButton("jungle_button", Vec2(), "worldmapB");
}

void cSelectStageScene::Update()
{
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("guide_close"))
		{
			isFirst = false;
		}
	}
}

void cSelectStageScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("WorldMap"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	RENDER->CenterRender(IMAGE->FindImage("WorldEmblem"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 600), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("church_lock"), Vec2(1000, 700), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("church_button"), Vec2(1000, 1000), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("city(night)_lock"), Vec2(2000, 1200), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("city(night)_button"), Vec2(2000, 1500), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("city_lock"), Vec2(500, 100), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("city_button"), Vec2(500, 400), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("desert_lock"), Vec2(2500, 800), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("desert_button"), Vec2(2500, 1100), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("ice_lock"), Vec2(1500, 1500), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("ice_button"), Vec2(1500, 1800), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("ocean_lock"), Vec2(3000, 1500), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("ocean_button"), Vec2(3000, 1800), 0.6);
	if (isFirst)
	{
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("guide_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_text2"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_close"), Vec2(3000, WINSIZEY / 2 - 1000));
	}
}

void cSelectStageScene::UIRender()
{
}

void cSelectStageScene::Release()
{
}
