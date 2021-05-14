#include "DXUT.h"
#include "cParentScene.h"

cParentScene::cParentScene()
{
}

cParentScene::~cParentScene()
{
	SAFE_DELETE(t_TextAni);
}

void cParentScene::Init()
{
	textCount = 1;
	isStart = false;
	isStop = false;
	isClear = false;
	isFail = false;
	percent = 0;
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
				textPos[i][j] = Vec2(-100, (float)WINSIZEY / 2);
			else if (j == 1)
				textPos[i][j] = Vec2((float)WINSIZEX / 2, (float)WINSIZEY / 2);
			else
				textPos[i][j] = Vec2((float)WINSIZEX + 500, (float)WINSIZEY / 2);
		}
	}

	BUTTON->AddButton("CFnext", Vec2(WINSIZEX / 2, WINSIZEY / 2 + 540), "ingameB");
}

void cParentScene::Update()
{
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("CFnext"))
		{
			if(isClear) SCENE->ChangeScene("cTitleScene");
			else if(isFail) SCENE->ChangeScene("cTitleScene");
			// 나중에 두 씬은 다르게
		}
	}
	if (!isStart)
	{
		if (t_TextAni != nullptr) t_TextAni->Update();

		if (!isStart && !isStop)
			StageStart(&textPos[textCount - 1][0], &textPos[textCount - 1][0], &textPos[textCount - 1][1], 0.1);

		if (t_TextAni == nullptr)
		{
			if (textCount < 6)
			{
				float time = 0;
				if (textCount == 5) time = 2;
				t_TextAni = new cTimer(1 + time, [&]()->void {
					t_TextAni = nullptr;
					if (!isStop)
						textCount++;
					if (textCount == 6) isStart = true;
					});
			}
		}
	}
}

void cParentScene::Render()
{
	if (!isStart)
	{
		switch (textCount)
		{
		case 1:
			RENDER->CenterRender(IMAGE->FindImage("start_3"), textPos[0][0]);
			break;
		case 2:
			RENDER->CenterRender(IMAGE->FindImage("start_2"), textPos[1][0]);
			break;
		case 3:
			RENDER->CenterRender(IMAGE->FindImage("start_1"), textPos[2][0]);
			break;
		case 4:
			RENDER->CenterRender(IMAGE->FindImage("start_start"), textPos[3][0]);
			break;
		case 5:
			RENDER->CenterRender(IMAGE->FindImage("start_game"), textPos[4][0]);
			break;
		default:
			break;
		}
	}

	if (isStop)
	{
		RENDER->CenterRender(IMAGE->FindImage("stop_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("stop_text"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 650));
		RENDER->CenterRender(IMAGE->FindImage("stop_back"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 300));
		RENDER->CenterRender(IMAGE->FindImage("stop_restart"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 400) + 400));
		RENDER->CenterRender(IMAGE->FindImage("stop_worldmap"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 500) + 800));
		RENDER->CenterRender(IMAGE->FindImage("stop_pointline"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	}

	if (isClear || isFail)
	{
		RENDER->CenterRender(IMAGE->FindImage("CFBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("CFpercent"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2 - 150));
		RENDER->CenterRender(IMAGE->FindImage("CFscore"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("CFtime"), Vec2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 150));
		RENDER->CenterRender(IMAGE->FindImage("CFgetItem"), Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 300));

		// 점령 확률, 스코어, 시간, 전리품 렌더하기

		(isClear) ? RENDER->CenterRender(IMAGE->FindImage("Clear"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 500)) : 
			RENDER->CenterRender(IMAGE->FindImage("Over"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 500));

		RENDER->CenterRender(IMAGE->FindImage("CFnext"), Vec2(WINSIZEX / 2, WINSIZEY / 2 + 540));
	}
}

void cParentScene::StageStart(Vec2* curPos_, Vec2* curPos, Vec2* targetPos, float speed)
{
	D3DXVec2Lerp(curPos_, curPos, targetPos, speed);
}

void cParentScene::StageClear()
{
}

void cParentScene::StageFail()
{
}

void cParentScene::SetPercent(float percent)
{
	this->percent = percent;
}

void cParentScene::SetScore(float score)
{
	this->score = score;
}