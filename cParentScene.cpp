#include "DXUT.h"
#include "cParentScene.h"

cParentScene::cParentScene()
{
}

cParentScene::~cParentScene()
{
}

void cParentScene::Init(string curScene)
{
	srand(time(NULL));

	SCENE->curScene = curScene;

	for (int i = 0; i < 7; i++)
	{
		textsPos[i] = Vec2(-100, WINSIZEY / 2);
	}

	memset(clear, false, sizeof(clear));
	memset(over, false, sizeof(over));
	memset(textRender, false, sizeof(textRender));

	alphaColor = 255;
	effectCount = 0;
	textCount = 1;
	percent = 0;
	timer = 180;
	CFCount = 0;
	speed = 100;
	SCENE->score = 0;
	delayCount = 0;
	hp = 3;
	score = 0;
	operValue = -1500;

	waitToStart = true;
	isFadeOut = true;
	once = true;
	isStart = isStop = isClear = isFail = isClearEnd = isFailEnd = delay = isdead = false;

	BUTTON->AddButton("CFnext", Vec2(WINSIZEX / 2, WINSIZEY / 2 + 540));

	BUTTON->AddButton("stop_back", Vec2(WINSIZEX / 2, WINSIZEY / 2 - 300));
	BUTTON->AddButton("stop_restart", Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 400) + 400));
	BUTTON->AddButton("stop_worldmap", Vec2(WINSIZEX / 2, (WINSIZEY / 2 - 500) + 800));

}

void cParentScene::Update()
{
	percent = player->coloring_per;
	hp = player->hp;
	playerPos = player->m_pos;
	score = SCENE->score;
	bossPos = mob->bossPos;

	if (t_Timer != nullptr) t_Timer->Update();
	if (t_Delay != nullptr) t_Delay->Update();
	if (t_WaitToStart != nullptr) t_WaitToStart->Update();
	if (t_TimeFade != nullptr) t_TimeFade->Update();
	if (t_CamMove != nullptr) t_CamMove->Update();
	if (t_EffectDelay != nullptr) t_EffectDelay->Update();

	SceneUpdate();

	if (waitToStart)
	{
		if (t_WaitToStart == nullptr)
			t_WaitToStart = new cTimer(4, [&]()->void {waitToStart = false;  t_WaitToStart = nullptr; });
	}
	if (!isStart)
	{
		if (t_TimeFade == nullptr)
		{
			t_TimeFade = new cTimer(0.5, [&]()->void {isFadeOut = !isFadeOut; t_TimeFade = nullptr; });
		}
	}
	else isFadeOut = false;

	if (INPUT->KeyDown(VK_ESCAPE) && isStart)
	{
		if (!isClear && !isFail)
		{
			isStop = !isStop;
		}
	}

	if (isStart && !isFail && !isStop && !isClear)
	{
		if (t_Timer == nullptr)
		{
			t_Timer = new cTimer(1, [&]()->void {
				if (timer > 0)
					timer--;
				t_Timer = nullptr;
				});
		}
	}

	if (isClear)
	{
		SOUND->Stop("draw_line");

		SCENE->gameClear = true;
		if (t_Clear != nullptr) t_Clear->Update();
		for (int x = 40; x < WINSIZEX - 40; x++)
			for (int y = 300; y < WINSIZEY - 40; y++)
				SCENE->Array[y][x] = 4;

		BG->high_BG = t_BG;

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
	else
	{
		BG->high_BG = nullptr;
	}

	if (isdead && once)
	{
		SOUND->Stop("draw_line");
		once = false;
		Vec2 movePos = playerPos;

		CAM->ZoomCam(0.1, 2, { WINSIZEX / 2, WINSIZEY / 2 });
		CAM->MoveCam(movePos);

		t_CamMove = new cTimer(3, [&]()->void {t_CamMove = nullptr; isFail = true; });
	}

	if (isFail)
	{
		SCENE->gameClear = false;
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
	if (MOUSE->lDown)
	{
		if (isClearEnd || isFailEnd)
		{
			if (MOUSE->LButtonClick("CFnext"))
			{
				if (isClearEnd)
					SCENE->m_rewards[SCENE->curScene] = 1;
				SCENE->ChangeScene("cEndScene");
			}
		}

		if (isStop)
		{
			if (MOUSE->LButtonClick("stop_back"))
			{
				isStop = false;
				MOUSE->lDown = false;
			}

			if (MOUSE->LButtonClick("stop_restart"))
			{
				SCENE->ChangeScene(SCENE->curScene);
				isStop = false;
				MOUSE->lDown = false;
			}

			if (MOUSE->LButtonClick("stop_worldmap"))
			{
				SCENE->ChangeScene("cSelectStageScene");
				isStop = false;
				MOUSE->lDown = false;
			}
		}
	}
	if (!waitToStart && !isStart)
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
	}
}

void cParentScene::Render()
{
	SceneRender();

	RENDER->CenterRender(IMAGE->FindImage("IngameBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
	RENDER->CenterRender(IMAGE->FindImage("hp_blind"), Vec2(270, 250));
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

	if (player->isHp)
	{
		RENDER->CenterRender(IMAGE->FindImage("Hp+"), Vec2(820, 125));
	}
	else
		RENDER->CenterRender(IMAGE->FindImage("Ingame_Item"), Vec2(820, 125));

	if (player->speedUp)
	{
		RENDER->CenterRender(IMAGE->FindImage("Speed+"), Vec2(1020, 125));
	}
	else
		RENDER->CenterRender(IMAGE->FindImage("Ingame_Item"), Vec2(1020, 125));
	if (player->invincibility)
	{
		RENDER->CenterRender(IMAGE->FindImage("Invincibility"), Vec2(1220, 125));
	}
	else
		RENDER->CenterRender(IMAGE->FindImage("Ingame_Item"), Vec2(1220, 125));

	if (!waitToStart && !isStart)
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
	RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(3750, 250), 1.2);

	if (!isFadeOut)
	{
		char time[5] = "";
		sprintf(time, "%d", timer / 60);
		RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 - 165, 320), 1.3);
		RENDER->CenterRender(IMAGE->FindImage("colon"), Vec2(WINSIZEX / 2 - 55, 320), 1.3);
		sprintf(time, "%d", (timer % 60) / 10);
		RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 + 65, 320), 1.3);
		sprintf(time, "%d", abs((timer % 60) - (((timer % 60) / 10) * 10)));
		RENDER->CenterRender(IMAGE->FindImage(time), Vec2(WINSIZEX / 2 + 165, 320), 1.3);
	}

	char t_score[5] = "";
	if (score > 9999) score = 9999;
	sprintf(t_score, "%d", score / 1000);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(2800, 175));
	sprintf(t_score, "%d", (score - ((score / 1000) * 1000)) / 100);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(2900, 175));
	sprintf(t_score, "%d", (score - ((score / 100) * 100)) / 10);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(3000, 175));
	sprintf(t_score, "%d", (score - ((score / 100) * 100)) % 10);
	RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(3100, 175));

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
		RENDER->CenterRender(IMAGE->FindImage("CFBG"), Vec2(WINSIZEX / 2, WINSIZEY / 2 + operValue));

		if (operValue < 0)
			operValue += 50;
		else
		{
			char key[5] = "";
			RENDER->CenterRender(IMAGE->FindImage("CFpercent"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2 - 170));
			sprintf(key, "%d", int(percent) / 10);
			RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 + 170, WINSIZEY / 2 - 170));
			sprintf(key, "%d", int(percent) % 10);
			RENDER->CenterRender(IMAGE->FindImage(key), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 - 170));
			RENDER->CenterRender(IMAGE->FindImage("percent"), Vec2(WINSIZEX / 2 + 340, WINSIZEY / 2 - 170));

			RENDER->CenterRender(IMAGE->FindImage("CFscore"), Vec2(WINSIZEX / 2 - 240, WINSIZEY / 2));
			char t_score[5] = "";
			sprintf(t_score, "%d", score / 1000);
			RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 115, WINSIZEY / 2));
			sprintf(t_score, "%d", (score - ((score / 1000) * 1000)) / 100);
			RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 195, WINSIZEY / 2));
			sprintf(t_score, "%d", (score - ((score / 100) * 100)) / 10);
			RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 275, WINSIZEY / 2));
			sprintf(t_score, "%d", (score - ((score / 100) * 100)) % 10);
			RENDER->CenterRender(IMAGE->FindImage(t_score), Vec2(WINSIZEX / 2 + 350, WINSIZEY / 2));

			char t_time[5] = "";
			int useTime = 180 - timer;
			sprintf(t_time, "%d", abs((useTime % 60) - (((useTime % 60) / 10) * 10))); // 1초의 자리..
			RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 340, WINSIZEY / 2 + 170));
			sprintf(t_time, "%d", (useTime % 60) / 10); // 10초의 자리..
			RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 260, WINSIZEY / 2 + 170));
			RENDER->CenterRender(IMAGE->FindImage("colon"), Vec2(WINSIZEX / 2 + 190, WINSIZEY / 2 + 170));
			sprintf(t_time, "%d", useTime / 60); // 1분의 자리..
			RENDER->CenterRender(IMAGE->FindImage(t_time), Vec2(WINSIZEX / 2 + 125, WINSIZEY / 2 + 170));

			RENDER->CenterRender(IMAGE->FindImage("CFtime"), Vec2(WINSIZEX / 2 - 200, WINSIZEY / 2 + 170));
			if (SCENE->m_rewards[SCENE->curScene] != 1 && !isFail)
			{
				RENDER->CenterRender(IMAGE->FindImage("CFgetItem"), Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 340));
				if (SCENE->curScene == "cChurchScene")
					RENDER->CenterRender(IMAGE->FindImage("church_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.4);
				else if (SCENE->curScene == "cCityScene")
					RENDER->CenterRender(IMAGE->FindImage("city_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.4);
				else if (SCENE->curScene == "cCityNightScene")
					RENDER->CenterRender(IMAGE->FindImage("city(night)_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.4);
				else if (SCENE->curScene == "cDesertScene")
					RENDER->CenterRender(IMAGE->FindImage("desert_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.3);
				else if (SCENE->curScene == "cIceScene")
					RENDER->CenterRender(IMAGE->FindImage("ice_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.4);
				else if (SCENE->curScene == "cJungleScene")
					RENDER->CenterRender(IMAGE->FindImage("jungle_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.4);
				else if (SCENE->curScene == "cOceanScene")
					RENDER->CenterRender(IMAGE->FindImage("ocean_item"), Vec2(WINSIZEX / 2 + 250, WINSIZEY / 2 + 340), 0.3);
			}

			RENDER->CenterRender(IMAGE->FindImage("CFnext"), Vec2(WINSIZEX / 2, WINSIZEY / 2 + 540));
		}
	}
}

bool fadeOut = true;
void cParentScene::UIRender()
{
	SceneUIRender();

	if (alphaColor >= 250)
	{
		fadeOut = true;
	}

	else if (alphaColor <= 5)
	{
		fadeOut = false;
	}

	//if (!waitToStart && !isStart)
	//	UI->CenterRender(IMAGE->FindImage("time_blind"),
	//		Vec2(1920 / 2 - 10, 160),
	//		0.5,
	//		D3DCOLOR_RGBA(255, 255, 255, fadeOut ? alphaColor -= 5 : alphaColor += 5));

	if (isClearEnd)
	{
		UI->CenterRender(IMAGE->FindImage("Clear"),
			Vec2(1920 / 2, 1080 / 2 - 225),
			0.4,
			D3DCOLOR_RGBA(255, 255, 255,
				fadeOut ? alphaColor -= 5 : alphaColor += 5));
	}

	else if (isFailEnd)
	{
		UI->CenterRender(IMAGE->FindImage("Over"),
			Vec2(1920 / 2, 1080 / 2 - 225),
			0.4,
			D3DCOLOR_RGBA(255, 255, 255,
				fadeOut ? alphaColor -= 2.5 : alphaColor += 2.5));
	}
}

void cParentScene::Release()
{
	SAFE_DELETE(t_TextAni);
	SAFE_DELETE(t_Timer);
	SAFE_DELETE(t_Clear);
	SAFE_DELETE(t_Over);
	SAFE_DELETE(t_Delay);
	SAFE_DELETE(t_TimeFade);
	SAFE_DELETE(t_WaitToStart);
	SAFE_DELETE(t_EffectDelay);
}

void cParentScene::PlayerDead()
{
	if (t_EffectDelay == nullptr && effectCount < 3)
	{
		DebugLog(L"effecting");
		t_EffectDelay = new cTimer(0.5, [&]()->void {
			for (int j = 0; j < 150; j++)
			{
				PART->AddEffect(playerPos + Vec2(rand() % 200 - 100, rand() % 200 - 100), 2, "red_effect");
			}
			SOUND->Play("attack", -3000);
			effectCount++;
			t_EffectDelay = nullptr;
			});
	}
	else if (effectCount >= 3)
	{
		player->render = false;
	}
}

void cParentScene::SceneUpdate()
{
	if (isStart)
	{
		if (timer <= 0 || player->hp <= 0 || INPUT->KeyDown('H'))
		{
			player->hp = 0;
			isdead = true;
			PlayerDead();
		}

		if (player->coloring_per >= 80 || INPUT->KeyDown('G'))
		{
			isClear = true;
		}

		if (mob->isDestroy)
		{
			SCENE->score += 300;
			mob->isDestroy = false;
		}
	}

	mob->Animation();
	player->CamEvent();
	if (isStart && !isStop)
	{
		if (!isdead && !isFail)
		{
			mob->Update();
			if (!isClear)
			{
				player->Update(mob->bossPos);
				bullet->Update();
				item->Update();
				coll->Update();
			}
		}
	}
}

void cParentScene::SceneRender()
{
	if (isStart && !isStop && !isFail && !isClear)
	{
		if (!isdead)
		{
			bullet->Render();
			item->Render();
		}
	}
	player->Render();

	if (!isClear)
		mob->Render();
}

void cParentScene::SceneUIRender()
{
	player->UIRender();
	mob->UIRender();
}
