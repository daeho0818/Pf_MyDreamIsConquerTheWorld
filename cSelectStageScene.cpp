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
	BUTTON->AddButton("guide_close", Vec2(3000, WINSIZEY / 2 - 1000));

	BUTTON->AddButton("church_button", Vec2(3100, 600), 0.6);
	BUTTON->AddButton("city_button", Vec2(2400, 900), 0.6);
	BUTTON->AddButton("city(night)_button", Vec2(1200, 1300), 0.6);
	BUTTON->AddButton("desert_button", Vec2(3500, 1800), 0.6);
	BUTTON->AddButton("ice_button", Vec2(600, 1900), 0.6);
	BUTTON->AddButton("ocean_button", Vec2(1000, 600), 0.6);
	BUTTON->AddButton("jungle_button", Vec2(3100, WINSIZEY / 2 + 100), 0.6);
	BUTTON->AddButton("StageStartB", Vec2(WINSIZEX / 2, WINSIZEY / 2 + 800), 0.6);
	BUTTON->AddButton("end_title", Vec2(WINSIZEX / 2, 2000), 0.8);
	BUTTON->AddButton("X", Vec2(WINSIZEX / 2 + 1060, WINSIZEY / 2 - 780), 0.6);
	stageOpen = false;
	stage = Stage::None;
	speed = 1;

	cloudsPos[0] = { 500, 500 };
	cloudsPos[1] = { WINSIZEX - 500, 500 };
	cloudsPos[2] = { WINSIZEX - 500, WINSIZEY };
	cloudsPos[3] = { 500, WINSIZEY };
}

void cSelectStageScene::Update()
{
	if (INPUT->KeyDown(VK_ESCAPE))
	{
		isFirst = false;
		stage = Stage::None;
	}

	if (MOUSE->lUp)
	{
		if (MOUSE->LButtonClick("guide_close"))
		{
			isFirst = false;
		}

		if (stage == Stage::None && !isFirst)
		{
			if (MOUSE->LButtonClick("church_button"))
			{
				stage = Stage::Church;
			}
			if (MOUSE->LButtonClick("city_button"))
			{
				stage = Stage::City;
			}
			if (MOUSE->LButtonClick("city(night)_button"))
			{
				stage = Stage::City_Night;
			}
			if (MOUSE->LButtonClick("desert_button"))
			{
				stage = Stage::Desert;
			}
			if (MOUSE->LButtonClick("ice_button"))
			{
				stage = Stage::Ice;
			}
			if (MOUSE->LButtonClick("ocean_button"))
			{
				stage = Stage::Ocean;
			}
			if (MOUSE->LButtonClick("jungle_button"))
			{
				stage = Stage::Jungle;
			}
			if (MOUSE->LButtonClick("end_title") && stage == Stage::None)
			{
				SCENE->ChangeScene("cTitleScene");
			}
		}
		else
		{
			Vec2 mousePos = Vec2(MOUSE->mousePos.x * 2.1, MOUSE->mousePos.y * 2.1);
			Vec2 buttonPos = { WINSIZEX / 2 + 1060, WINSIZEY / 2 - 780 };
			if (mousePos.x >= buttonPos.x - (IMAGE->FindImage("X")->info.Width * 0.6 / 2) &&
				mousePos.x <= buttonPos.x + (IMAGE->FindImage("X")->info.Width * 0.6 / 2) &&
				mousePos.y >= buttonPos.y - (IMAGE->FindImage("X")->info.Height * 0.6 / 2) &&
				mousePos.y <= buttonPos.y + (IMAGE->FindImage("X")->info.Height * 0.6 / 2))
			{
				stage = Stage::None;
				MOUSE->lUp = false;
			}
			if (MOUSE->LButtonClick("StageStartB"))
			{
				SceneChange(stage);
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		cloudsPos[i].y += speed;
		if (cloudsPos[i].y >= WINSIZEY + 1000) cloudsPos[i].y = -1000;
	}

}

void cSelectStageScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("WorldMap"), Vec2(WINSIZEX / 2, WINSIZEY / 2));

	RENDER->CenterRender(IMAGE->FindImage("church_lock"), Vec2(3100, 300), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("church_button"), Vec2(3100, 600), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("city(night)_lock"), Vec2(1200, 1000), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("city(night)_button"), Vec2(1200, 1300), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("city_lock"), Vec2(2400, 600), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("city_button"), Vec2(2400, 900), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("desert_lock"), Vec2(3500, 1500), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("desert_button"), Vec2(3500, 1800), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("ice_lock"), Vec2(600, 1600), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("ice_button"), Vec2(600, 1900), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("ocean_lock"), Vec2(1000, 300), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("ocean_button"), Vec2(1000, 600), 0.6);

	RENDER->CenterRender(IMAGE->FindImage("jungle_lock"), Vec2(3100, WINSIZEY / 2 - 200), 0.6);
	RENDER->CenterRender(IMAGE->FindImage("jungle_button"), Vec2(3100, WINSIZEY / 2 + 100), 0.6);


	RENDER->CenterRender(IMAGE->FindImage("cloud1"), cloudsPos[0]);
	RENDER->CenterRender(IMAGE->FindImage("cloud2"), cloudsPos[1]);
	RENDER->CenterRender(IMAGE->FindImage("cloud3"), cloudsPos[2]);
	RENDER->CenterRender(IMAGE->FindImage("cloud4"), cloudsPos[3]);

	RENDER->CenterRender(IMAGE->FindImage("end_title"), Vec2(WINSIZEX / 2, 2000), 0.8);

	StageInfo(stage);

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
	for (auto iter : BUTTON->m_buttons)
	{
		SAFE_DELETE(iter);
	}
	BUTTON->m_buttons.clear();
}

void cSelectStageScene::StageInfo(Stage stage)
{
	switch (stage)
	{
	case Stage::Church:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("church_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::City:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("city_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::City_Night:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("city(night)_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::Ice:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("ice_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::Desert:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("desert_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::Jungle:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("jungle_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	case Stage::Ocean:
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("ocean_All"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.7);
		break;
	default:
		break;
	}
	if (stage != Stage::None)
	{
		RENDER->CenterRender(IMAGE->FindImage("StageStartB"), Vec2(WINSIZEX / 2, WINSIZEY / 2 + 800), 0.6);
		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(WINSIZEX / 2 + 1060, WINSIZEY / 2 - 780), 0.6);
	}
}

void cSelectStageScene::SceneChange(Stage stage)
{
	switch (stage)
	{
	case Stage::Church:
		SCENE->ChangeScene("cChurchScene");
		break;
	case Stage::City:
		SCENE->ChangeScene("cCityScene");
		break;
	case Stage::City_Night:
		SCENE->ChangeScene("cCityNightScene");
		break;
	case Stage::Desert:
		SCENE->ChangeScene("cDesertScene");
		break;
	case Stage::Ice:
		SCENE->ChangeScene("cIceScene");
		break;
	case Stage::Jungle:
		SCENE->ChangeScene("cJungleScene");
		break;
	case Stage::Ocean:
		SCENE->ChangeScene("cOceanScene");
		break;
	}
}