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
	if (t_AniTerm != nullptr) t_AniTerm->Update();

	if (!isAniStart && t_AniTerm == nullptr)
	{
		t_AniTerm = new cTimer(5, [&]()->void {isAniStart = true; t_AniTerm = nullptr; });
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

	for (int i = -4; i < 5; i++)
		RENDER->CenterRender(IMAGE->FindImage("player"), Vec2(WINSIZEX / 2 + (i * 100), WINSIZEY / 2 + operY[i + 4]));
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
