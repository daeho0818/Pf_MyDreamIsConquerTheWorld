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
	BUTTON->AddButton("start_button", Vec2(600, 250), 0.6);
	BUTTON->AddButton("guide_button", Vec2(600, 650), 0.6);
	BUTTON->AddButton("adven_button", Vec2(600, 1050), 0.6);
	BUTTON->AddButton("develop_button", Vec2(600, 1450), 0.6);
	BUTTON->AddButton("quit_button", Vec2(600, 1850), 0.6);

	BUTTON->AddButton("guide_close", Vec2(3000, WINSIZEY / 2 - 1000));
	BUTTON->AddButton("X", Vec2(3330, WINSIZEY / 2 - 1023), 0.6);

	BUTTON->AddButton("Arrow", Vec2(500, 2100), 1.5);

	guideUI = false;
	advenUI = false;
	developUI = false;
	buttonsMoved = false;
	movedEnd = true;
	temp = 0;
	count = 0;
	logoPos = { WINSIZEX / 2, 500 }; 
	arrowKey = "Arrow";
	memset(move, false, sizeof(move));
	move[0] = true; speed = 1;

	tempFunc = [=](int index) -> void {
		switch (index)
		{
		case 0:
			RENDER->CenterRender(IMAGE->FindImage("start_button"), Vec2(600, 250 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("start_note"), { 170, 250 - temp });
			break;
		case 1:
			RENDER->CenterRender(IMAGE->FindImage("guide_button"), Vec2(600, 650 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("guide_note"), { 170, 650 - temp });
			break;
		case 2:
			RENDER->CenterRender(IMAGE->FindImage("adven_button"), Vec2(600, 1050 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("adven_note"), { 170, 1050 - temp });
			break;
		case 3:
			RENDER->CenterRender(IMAGE->FindImage("develop_button"), Vec2(600, 1450 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("develop_note"), { 170, 1450 - temp });
			break;
		case 4:
			RENDER->CenterRender(IMAGE->FindImage("quit_button"), Vec2(600, 1850 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("quit_note"), { 170, 1850 - temp });
			break;
		}
	};

	BUTTON->ChangeBtnInfo("Arrow", { 500, 2100 }, 1.5f);
}

void cTitleScene::Update()
{
	if (t_Delay != nullptr) t_Delay->Update();
	if (guideUI) if (INPUT->KeyDown(VK_ESCAPE)) guideUI = false;
	if (advenUI) if (INPUT->KeyDown(VK_ESCAPE)) advenUI = false;
	if (developUI) if (INPUT->KeyDown(VK_ESCAPE)) developUI = false;

	speed += 0.5;
	logoPos.y += sin(0.1 * speed);

	if (buttonsMoved)
	{
		if (t_Delay == nullptr && count <= 19)
		{
			t_Delay = new cTimer(0.01, [&]()->void {
				for (auto iter : BUTTON->m_buttons)
				{
					if (movedEnd)
						iter->m_pos -= Vec2(0, 100);
					else
						iter->m_pos += Vec2(0, 100);
				}
				if (movedEnd)
					temp += 100;
				else
					temp -= 100;

				count++;
				t_Delay = nullptr;
				});
		}
		else if (count > 19)
		{
			if (movedEnd)
				BUTTON->ChangeBtnInfo("Arrow", { 500, 100 }, 1.5f);
			else
				BUTTON->ChangeBtnInfo("Arrow", { 500, 2100 }, 1.5f);
			movedEnd = !movedEnd;
			if (movedEnd)
				arrowKey = "Arrow";
			else
				arrowKey = "_Arrow";
			buttonsMoved = false;
			count = 0;
		}
	}
	if (MOUSE->lUp)
	{
		if (!buttonsMoved && movedEnd)
		{
			if (MOUSE->LButtonClick("start_button"))
			{
				if (!guideUI && !advenUI && !developUI)
					SCENE->ChangeScene("cSelectStageScene");
			}
			else if (MOUSE->LButtonClick("guide_button"))
			{
				if (!guideUI && !advenUI && !developUI)
					guideUI = true;
			}
			else if (MOUSE->LButtonClick("adven_button"))
			{
				DebugParam(L"%d", SCENE->a_rewards[0]);
				if (!advenUI && !guideUI && !developUI)
					advenUI = true;
			}
			else if (MOUSE->LButtonClick("develop_button"))
			{
				developUI = true;
			}
			else if (MOUSE->LButtonClick("quit_button"))
			{
				if (!advenUI && !guideUI && !developUI)
					PostQuitMessage(0);
			}
			else if (MOUSE->LButtonClick("guide_close"))
			{
				if (guideUI)
				{
					guideUI = false;
				}
			}
		}
		if (MOUSE->LButtonClick("X"))
		{
			if (advenUI)
			{
				advenUI = false;
			}
			if (developUI)
			{
				developUI = false;
			}
		}
		if (MOUSE->LButtonClick("Arrow") && !buttonsMoved)
		{
			if (!guideUI && !advenUI && !developUI)
				buttonsMoved = true;
		}
		MOUSE->lUp = false;
	}
}

void cTitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(IMAGE->FindImage("Logo"), { logoPos.x, logoPos.y - temp }, 0.5);
	RENDER->CenterRender(IMAGE->FindImage("pattern"), { 500, 1000 - temp });

	RENDER->CenterRender(IMAGE->FindImage(arrowKey), Vec2(500, 2100 - temp), 1.5);

	if (!guideUI && !advenUI && !developUI)
	{
		MOUSE->Collider("start_button") ?
			MOUSE->lStay && MOUSE->Collider("start_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Start"), Vec2(600, 250 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Start"), Vec2(600, 250 - temp)) :
			tempFunc(0);

		MOUSE->Collider("guide_button") ?
			MOUSE->lStay && MOUSE->Collider("guide_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Guide"), Vec2(600, 650 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Guide"), Vec2(600, 650 - temp)) :
			tempFunc(1);

		MOUSE->Collider("adven_button") ?
			MOUSE->lStay && MOUSE->Collider("adven_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Adven"), Vec2(600, 1050 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Adven"), Vec2(600, 1050 - temp)) :
			tempFunc(2);

		MOUSE->Collider("develop_button") ?
			MOUSE->lStay && MOUSE->Collider("develop_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Develop"), Vec2(600, 1450 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Develop"), Vec2(600, 1450 - temp)) :
			tempFunc(3);

		MOUSE->Collider("quit_button") ?
			MOUSE->lStay && MOUSE->Collider("quit_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Quit"), Vec2(600, 1850 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Quit"), Vec2(600, 1850 - temp)) :
			tempFunc(4);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			tempFunc(i);
	}

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
		RENDER->CenterRender(IMAGE->FindImage("adven_BG"), Vec2(WINSIZEX / 2 + 25, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("adven_BGRect"), Vec2(WINSIZEX / 2 + 25, WINSIZEY / 2), 0.8);

		for (int i = 1; i < 5; i++)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_ItemRect"), Vec2(900, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentBG"), Vec2(1525, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_textBG"), Vec2(1525, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentRect"), Vec2(1525, 450 * i), 0.3);
			if (SCENE->a_rewards[i - 1] == 1)
				printf("heehee");
			else
			{
				RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(900, 450 * i), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_Lock"), Vec2(900, 450 * i + 40), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1400, 450 * i), 0.25);
			}
		}

		for (int i = 1; i < 4; i++)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_ItemRect"), Vec2(2180, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentBG"), Vec2(2805, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_textBG"), Vec2(2805, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentRect"), Vec2(2805, 450 * i), 0.3);
			if (SCENE->a_rewards[(i - 1) + 4] != 1)
			{
				RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(2180, 450 * i), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_Lock"), Vec2(2180, 450 * i + 40), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(2725, 450 * i), 0.25);
			}
		}

		RENDER->CenterRender(IMAGE->FindImage("symbol_church"), Vec2(1850, 410), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_church_name"), Vec2(1850, 530), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_city"), Vec2(1850, 860), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_city_name"), Vec2(1850, 970), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_city(night)"), Vec2(1850, 1310), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_city(night)_name"), Vec2(1850, 1420), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_desert"), Vec2(1850, 1750), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_desert_name"), Vec2(1850, 1860), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_jungle"), Vec2(3140, 400), 0.25);
		RENDER->CenterRender(IMAGE->FindImage("symbol_jungle_name"), Vec2(3140, 510), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_ice"), Vec2(3140, 860), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_ice_name"), Vec2(3140, 970), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_ocean"), Vec2(3140, 1300), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_ocean_name"), Vec2(3140, 1410), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPerBG"), Vec2(350, WINSIZEY - 420), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPer"), Vec2(350, WINSIZEY - 420), 0.7);

		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(3330, WINSIZEY / 2 - 1023), 0.6);
		BUTTON->ChangeBtnInfo("X", Vec2(3330, WINSIZEY / 2 - 1023), 0.6);
	}
	else if (developUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Credit"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 2.5);
		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(3900, WINSIZEY / 2 - 1023), 0.6);
		BUTTON->ChangeBtnInfo("X", Vec2(3900, WINSIZEY / 2 - 1023), 0.6);
	}
}

void cTitleScene::UIRender()
{

}

void cTitleScene::Release()
{
	for (auto iter : BUTTON->m_buttons) SAFE_DELETE(iter);
	BUTTON->m_buttons.clear();
	SAFE_DELETE(t_Delay);
}
