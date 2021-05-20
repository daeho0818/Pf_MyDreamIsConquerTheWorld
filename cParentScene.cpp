#include "DXUT.h"
#include "cParentScene.h"

cParentScene::cParentScene()
{
}

cParentScene::~cParentScene()
{
	SAFE_DELETE(t_TextAni);
	SAFE_DELETE(t_Timer);
	SAFE_DELETE(t_Clear);
	SAFE_DELETE(t_Over);
	SAFE_DELETE(t_Delay);
}

void cParentScene::Init(string curScene)
{
	SCENE->curScene = curScene;

	textCount = 1;
	percent = 0;
	score = 0;
	timer = 180;
	CFCount = 0;
	speed = 100;
	delayCount = 0;
	hp = 3;

	isStart = false;
	isStop = false;
	isClear = false;
	isFail = false;
	isClearEnd = false;
	isFailEnd = false;
	delay = false;

	for (int i = 0; i < 7; i++)
	{
		textsPos[i] = Vec2(-100, WINSIZEY / 2);
	}

	memset(clear, false, sizeof(clear));
	memset(over, false, sizeof(over));
	memset(textRender, false, sizeof(textRender));

	t_TextAni = nullptr;
	t_Timer = nullptr;
	t_Clear = nullptr;
	t_Over = nullptr;
	t_Delay = nullptr;

	BUTTON->AddButton("CFnext", Vec2(WINSIZEX / 2, WINSIZEY / 2 + 540), "ingameB");

	BUTTON->AddButton("stop_back", Vec2(WINSIZEX / 2, WINSIZEY / 2 - 300), "stopB");
	BUTTON->AddButton("stop_restart", Vec2(WINSIZEX / 2, WINSIZEY / 2 - 400), "stopB");
	BUTTON->AddButton("stop_worldmap", Vec2(WINSIZEX / 2, WINSIZEY / 2 - 500), "stopB");
}

void cParentScene::Update()
{
	if (INPUT->KeyDown('G')) isClear = true;
	if (INPUT->KeyDown('H')) isFail = true;

	if (t_Timer != nullptr) t_Timer->Update();
	if (t_Delay != nullptr) t_Delay->Update();

	if (isStart && !isFail && !isStop && !isClear)
	{
		if (t_Timer == nullptr)
		{
			t_Timer = new cTimer(1, [&]()->void {
				timer--;
				t_Timer = nullptr;
				});
		}
	}

	if (isClear)
	{
		if (t_Clear != nullptr) t_Clear->Update();

		if (delay)
		{
			if (delayCount < 7)
			{
				if (t_Delay == nullptr)
				{
					t_Delay = new cTimer(0.2, [&]()->void {
						clear[delayCount] = true;
						delayCount++;
						t_Delay = nullptr;
						});
				}
			}
		}

		if (t_Clear == nullptr)
		{
			if (CFCount < 7)
			{
				t_Clear = new cTimer(0.2, [&]()->void {
					textRender[CFCount] = true;
					clear[CFCount] = true;
					CFCount++;
					t_Clear = nullptr;
					});
			}
		}
		if (clear[0])
		{
			textsPos[0].x += speed;
		}
		if (clear[1])
		{
			textsPos[1].x += speed;
		}
		if (clear[2])
		{
			textsPos[2].x += speed;
		}
		if (clear[3])
		{
			textsPos[3].x += speed;
		}
		if (clear[4])
		{
			textsPos[4].x += speed;
		}
		if (clear[5])
		{
			textsPos[5].x += speed;
		}
		if (clear[6])
		{
			textsPos[6].x += speed;
		}
	}

	if (isFail)
	{
		if (t_Over != nullptr) t_Over->Update();

		if (t_Over == nullptr)
		{
			if (CFCount < 5)
			{
				t_Over = new cTimer(0.2, [&]()->void {
					textRender[CFCount] = true;
					over[CFCount] = true;
					CFCount++;
					t_Over = nullptr;
					});
			}
		}

		if (delay)
		{
			if (delayCount < 5)
			{
				if (t_Delay == nullptr)
				{
					t_Delay = new cTimer(0.2, [&]()->void {
						over[delayCount] = true;
						delayCount++;
						t_Delay = nullptr;
						});
				}
			}
		}

		if (over[0])
		{
			textsPos[0].x += speed;
		}
		if (over[1])
		{
			textsPos[1].x += speed;
		}
		if (over[2])
		{
			textsPos[2].x += speed;
		}
		if (over[3])
		{
			textsPos[3].x += speed;
		}
	}

	if (!delay)
	{

		if (isClear)
		{
			for (int i = 0; i < 7; i++)
			{
				if (clear[i])
				{
					if (textsPos[i].x >= 2600 - i * 200)
					{
						clear[i] = false;
					}
					if (!clear[0] && !clear[1] && !clear[2] && !clear[3] && !clear[4] && !clear[5] && !clear[6])
					{
						t_Clear = new cTimer(2, [&]()->void {
							t_Clear = nullptr;
							delay = true;
							});
					}
				}
			}
		}
		if (isFail)
		{
			for (int i = 0; i < 4; i++)
			{
				if (over[i])
				{
					if (textsPos[i].x >= 2300 - i * 200)
					{
						over[i] = false;
					}
					if (!over[0] && !over[1] && !over[2] && !over[3])
					{
						t_Over = new cTimer(2, [&]()->void {
							t_Over = nullptr;
							delay = true;
							});
					}
				}
			}
		}
	}
	else
	{
		if (isClear)
		{
			if (textsPos[6].x >= WINSIZEX + 100)
			{
				isClearEnd = true;
			}
		}
		else if (isFail)
		{
			if (textsPos[3].x >= WINSIZEX + 100)
			{
				isFailEnd = true;
			}
		}
	}
	if (MOUSE->lUp)
	{
		if (MOUSE->Collider("CFnext"))
		{
			if (isClearEnd) SCENE->ChangeScene("cEndScene");
			else if (isFailEnd) SCENE->ChangeScene("cEndScene");
		}

		if (isStop)
		{
			if (MOUSE->Collider("stop_back"))
			{
				isStop = false;
			}

			if (MOUSE->Collider("stop_restart"))
			{
				SCENE->ChangeScene(SCENE->curScene);
			}

			if (MOUSE->Collider("stop_worldmap"))
			{
				SCENE->ChangeScene("cSelectStageScene");
			}
		}
	}
	if (!isStart)
	{
		if (t_TextAni != nullptr) t_TextAni->Update();

		if (t_TextAni == nullptr)
		{
			if (textCount < 5)
			{
				t_TextAni = new cTimer(1, [&]()->void {
					t_TextAni = nullptr;
					if (!isStop) textCount++;
					if (textCount == 5) isStart = true;
					});
			}
		}
		//if (!isStart && !isStop)
		//	StageStart(&textPos[textCount - 1][0], &textPos[textCount - 1][0], &textPos[textCount - 1][1], 0.1);

		//if (t_TextAni == nullptr)
		//{
		//	if (textCount < 6)
		//	{
		//		float time = 0;
		//		if (textCount == 1) time = 1;
		//		t_TextAni = new cTimer(1 + time, [&]()->void {
		//			t_TextAni = nullptr;
		//			if (!isStop)
		//				textCount++;
		//			if (textCount == 6) isStart = true;
		//			});
		//	}
		//}
	}
}

void cParentScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("IngameBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	switch (hp)
	{
	case 3:
		RENDER->CenterRender(IMAGE->FindImage("Ingame_HP3"), Vec2(270, 250));
		break;
	case 2:
		RENDER->CenterRender(IMAGE->FindImage("Ingame_HP2"), Vec2(270, 250));
		break;
	case 1:
		RENDER->CenterRender(IMAGE->FindImage("Ingame_HP1"), Vec2(270, 250));
		break;
	case 0:
		RENDER->CenterRender(IMAGE->FindImage("Ingame_HP0"), Vec2(270, 250));
		break;
	}
	RENDER->CenterRender(IMAGE->FindImage("Ingame_HP"), Vec2(270, 250));

	RENDER->CenterRender(IMAGE->FindImage("Ingame_Item"), Vec2(1200, 75));

	if (!isStart)
	{
		RENDER->CenterRender(IMAGE->FindImage("start_game"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 125));
		switch (textCount)
		{
		case 1:
			RENDER->CenterRender(IMAGE->FindImage("start_3"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
			break;
		case 2:
			RENDER->CenterRender(IMAGE->FindImage("start_2"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
			break;
		case 3:
			RENDER->CenterRender(IMAGE->FindImage("start_1"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
			break;
		case 4:
			RENDER->CenterRender(IMAGE->FindImage("start_start"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
			break;
		default:
			break;
		}
	}

	char key[5] = "";
	if (percent >= 100) percent = 95;
	sprintf(key, "%d", (int)percent / 10);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(3500, 250), 1.2);
	sprintf(key, "%d", (int)percent % 10);
	RENDER->CenterRender(IMAGE->FindImage(key), Vec2(3600, 250), 1.2);
	RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(3700, 250), 1.2);

	char time[5] = "";
	sprintf(time, "%d", timer / 60);
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 - 200, 320), 1.3);
	sprintf(time, "%d", (timer % 60) / 10);
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 + 30, 320), 1.3);
	sprintf(time, "%d", abs((timer % 60) - (((timer % 60) / 10) * 10)));
	RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 + 130, 320), 1.3);

	char t_score[5] = "";
	sprintf(t_score, "%d", score / 1000);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(2800, 190));
	sprintf(t_score, "%d", (score - ((score / 1000) * 1000)) / 100);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(2900, 190));
	sprintf(t_score, "%d", (score- ((score / 100) * 100)) / 10);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(3000, 190));
	sprintf(t_score, "%d",( score - ((score / 100) * 100)) % 10);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(3100, 190));

	if (isStop)
	{
		RENDER->CenterRender(IMAGE->FindImage("stop_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("stop_text"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 650));
		RENDER->CenterRender(IMAGE->FindImage("stop_back"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 300));
		RENDER->CenterRender(IMAGE->FindImage("stop_restart"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 400) + 400));
		RENDER->CenterRender(IMAGE->FindImage("stop_worldmap"), Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 500) + 800));
		RENDER->CenterRender(IMAGE->FindImage("stop_pointline"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	}

	if (isClear)
	{
		if (textRender[0])
		{
			RENDER->CenterRender(IMAGE->FindImage("!"), textsPos[0]);
		}
		if (textRender[1])
		{
			RENDER->CenterRender(IMAGE->FindImage("!"), textsPos[1]);
		}
		if (textRender[2])
		{
			RENDER->CenterRender(IMAGE->FindImage("R"), textsPos[2]);
		}
		if (textRender[3])
		{
			RENDER->CenterRender(IMAGE->FindImage("A"), textsPos[3]);
		}
		if (textRender[4])
		{
			RENDER->CenterRender(IMAGE->FindImage("E"), textsPos[4]);
		}
		if (textRender[5])
		{
			RENDER->CenterRender(IMAGE->FindImage("L"), textsPos[5]);
		}
		if (textRender[6])
		{
			RENDER->CenterRender(IMAGE->FindImage("C"), textsPos[6]);
		}
	}

	if (isFail)
	{
		if (textRender[0])
		{
			RENDER->CenterRender(IMAGE->FindImage("OVER_R"), textsPos[0]);
		}
		if (textRender[1])
		{
			RENDER->CenterRender(IMAGE->FindImage("OVER_E"), textsPos[1]);
		}
		if (textRender[2])
		{
			RENDER->CenterRender(IMAGE->FindImage("V"), textsPos[2]);
		}
		if (textRender[3])
		{
			RENDER->CenterRender(IMAGE->FindImage("O"), textsPos[3]);
		}
	}

	if (isClearEnd || isFailEnd)
	{
		char key[5] = "";
		RENDER->CenterRender(IMAGE->FindImage("CFBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("CFpercent"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2 - 150));
		sprintf(key, "%d", int(percent) / 10);
		RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 + 160, WINSIZEY / 2 - 150));
		sprintf(key, "%d", int(percent) % 10);
		RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 + 240, WINSIZEY / 2 - 150));
		RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(WINSIZEX / 2 + 340, WINSIZEY / 2 - 150));

		RENDER->CenterRender(IMAGE->FindImage("CFscore"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2));
		char t_score[5] = "";
		sprintf(t_score, "%d", score / 1000);
		RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 40, WINSIZEY / 2));
		sprintf(t_score, "%d", (score - ((score / 1000) * 1000)) / 100);
		RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 140, WINSIZEY / 2));
		sprintf(t_score, "%d", (score - ((score / 100) * 100)) / 10);
		RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 240, WINSIZEY / 2));
		sprintf(t_score, "%d", (score - ((score / 100) * 100)) % 10);
		RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 340, WINSIZEY / 2));

		char t_time[5] = "";
		int useTime = 180 - timer;
		sprintf(t_time, "%d", abs((useTime % 60) - (((useTime % 60) / 10) * 10)));
		RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 340, WINSIZEY / 2 + 150));
		sprintf(t_time, "%d", (useTime % 60) / 10);
		RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 240, WINSIZEY / 2 + 150));
		sprintf(t_time, "%d", useTime / 60);
		RENDER->CenterRender(IMAGE->FindImage("colon"), Vec2(WINSIZEX / 2 + 165, WINSIZEY / 2 + 150));
		RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 90, WINSIZEY / 2 + 150));
		RENDER->CenterRender(IMAGE->FindImage("CFtime"), Vec2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 150));
		RENDER->CenterRender(IMAGE->FindImage("CFgetItem"), Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 300));

		(isClearEnd) ? RENDER->CenterRender(IMAGE->FindImage("Clear"), Vec2(WINSIZEX / 2, WINSIZEY / 2 - 500)) :
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

void cParentScene::SetHP(int hp)
{
	this->hp = hp;
}