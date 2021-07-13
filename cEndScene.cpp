#include "DXUT.h"
#include "cEndScene.h"

cEndScene::cEndScene()
{
}

cEndScene::~cEndScene()
{
	for (auto iter : BUTTON->m_buttons)
	{
		SAFE_DELETE(iter);
	}
	BUTTON->m_buttons.clear();
}

void cEndScene::Init()
{
	count = 0;
	index = 0;
	memset(operY, 0, sizeof(operY));

	isAniStart = true;
	isTextUp = true;

	BUTTON->AddButton("end_restart", Vec2(WINSIZEX / 2 - ((WINSIZEX / 2) / 2), 2000), 0.8);
	BUTTON->AddButton("end_title", Vec2(WINSIZEX / 2, 2000), 0.8);
	BUTTON->AddButton("end_worldmap", Vec2(WINSIZEX / 2 + ((WINSIZEX / 2) / 2), 2000), 0.8);
}

void cEndScene::Update()
{
	if (t_AniDelay != nullptr) t_AniDelay->Update();
	// if (t_AniTerm != nullptr) t_AniTerm->Update();

	if (!isAniStart/* && t_AniTerm == nullptr*/)
	{
		isAniStart = true;
	}

	if (isAniStart && t_AniDelay == nullptr)
	{
		t_AniDelay = new cTimer(0.01, [&]()->void {TextUpOrDown(); });
	}

	if (MOUSE->lUp)
	{
		if (MOUSE->LButtonClick("end_restart"))
		{
			BG->high_BG = nullptr;
			SCENE->ChangeScene(SCENE->curScene);
		}
		if (MOUSE->LButtonClick("end_title"))
		{
			SCENE->ChangeScene("cTitleScene");
		}
		if (MOUSE->LButtonClick("end_worldmap"))
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

	float interval = 200;
	if (SCENE->gameClear)
	{
		RENDER->CenterRender(IMAGE->FindImage("G"), Vec2(WINSIZEX / 2 - 50 - interval * 4, WINSIZEY / 2 - 400 + operY[0]));
		RENDER->CenterRender(IMAGE->FindImage("A"), Vec2(WINSIZEX / 2 - 50 - interval * 3, WINSIZEY / 2 - 400 + operY[1]));
		RENDER->CenterRender(IMAGE->FindImage("M"), Vec2(WINSIZEX / 2 - 50 - interval * 2, WINSIZEY / 2 - 400 + operY[2]));
		RENDER->CenterRender(IMAGE->FindImage("E"), Vec2(WINSIZEX / 2 - 50 - interval, WINSIZEY / 2 - 400 + operY[3]));
		RENDER->CenterRender(IMAGE->FindImage("C"), Vec2(WINSIZEX / 2 + 50, WINSIZEY / 2 - 400 + operY[4]));
		RENDER->CenterRender(IMAGE->FindImage("L"), Vec2(WINSIZEX / 2 + 50 + interval, WINSIZEY / 2 - 400 + operY[5]));
		RENDER->CenterRender(IMAGE->FindImage("E"), Vec2(WINSIZEX / 2 + 50 + interval * 2, WINSIZEY / 2 - 400 + operY[6]));
		RENDER->CenterRender(IMAGE->FindImage("A"), Vec2(WINSIZEX / 2 + 50 + interval * 3, WINSIZEY / 2 - 400 + operY[7]));
		RENDER->CenterRender(IMAGE->FindImage("R"), Vec2(WINSIZEX / 2 + 50 + interval * 4, WINSIZEY / 2 - 400 + operY[8]));
	}
	else
	{
		RENDER->CenterRender(IMAGE->FindImage("OVER_G"), Vec2(WINSIZEX / 2 - interval * 4, WINSIZEY / 2 - 400  + operY[0]));
		RENDER->CenterRender(IMAGE->FindImage("OVER_A"), Vec2(WINSIZEX / 2 - interval * 3, WINSIZEY / 2 - 400 + operY[1]));
		RENDER->CenterRender(IMAGE->FindImage("OVER_M"), Vec2(WINSIZEX / 2 - interval * 2, WINSIZEY / 2 - 400  + operY[2]));
		RENDER->CenterRender(IMAGE->FindImage("OVER_E"), Vec2(WINSIZEX / 2 - interval, WINSIZEY / 2 - 400 + operY[3]));
		RENDER->CenterRender(IMAGE->FindImage("O"), Vec2(WINSIZEX / 2 + interval, WINSIZEY / 2 - 400 + operY[4]));
		RENDER->CenterRender(IMAGE->FindImage("V"), Vec2(WINSIZEX / 2 + interval * 2, WINSIZEY / 2 - 400 + operY[5]));
		RENDER->CenterRender(IMAGE->FindImage("OVER_E"), Vec2(WINSIZEX / 2 + interval * 3, WINSIZEY / 2 - 400 + operY[6]));
		RENDER->CenterRender(IMAGE->FindImage("OVER_R"), Vec2(WINSIZEX / 2 + interval * 4, WINSIZEY / 2 - 400 + operY[7]));
	}
}

void cEndScene::UIRender()
{
}

void cEndScene::Release()
{
}

void cEndScene::TextUpOrDown()
{
	if (count < 10)
	{
		if (isTextUp)
		{
			operY[index] -= 5;
		}
		else
		{
			operY[index] += 5;
		}
		count++;
	}
	else
	{
		if (!isTextUp)
		{
			index++;
			if (index >= 9)
			{
				index = 0;
				isAniStart = false;
			}
		}
		isTextUp = !isTextUp;
		count = 0;
	}
	t_AniDelay = nullptr;
}
