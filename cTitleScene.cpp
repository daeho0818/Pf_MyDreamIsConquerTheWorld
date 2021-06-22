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
	BUTTON->AddButton("X", Vec2(3330, WINSIZEY / 2 - 1023), "worldmapB");

	BUTTON->AddButton("Arrow", Vec2(500, 2100), "arrowB");

	guideUI = false;
	advenUI = false;
	buttonsMoved = false;
	movedEnd = true;
	temp = 0;
	logoPos = { WINSIZEX / 2, 500 };
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
}

void cTitleScene::Update()
{
	if (t_Delay != nullptr) t_Delay->Update();
	if (guideUI) if (INPUT->KeyDown(VK_ESCAPE)) guideUI = false;
	if (advenUI) if (INPUT->KeyDown(VK_ESCAPE)) advenUI = false;

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
				BUTTON->ChangeBtnInfo("Arrow", { 500, 100 }, "arrowB");
			else
				BUTTON->ChangeBtnInfo("Arrow", { 500, 2100 }, "arrowB");
			movedEnd = !movedEnd;
			if (!movedEnd)
				arrowKey = "_Arrow";
			else
				arrowKey = "Arrow";
			buttonsMoved = false;
			count = 0;
		}
	}

	if (MOUSE->lDown)
	{
		downPos = Vec2(MOUSE->mousePos.x, MOUSE->mousePos.y);
		MOUSE->lDown = false;
	}

	if (MOUSE->lUp)
	{
		if (!buttonsMoved && movedEnd)
		{
			if (MOUSE->Collider("start_button") && MOUSE->Collider("start_button", downPos))
			{
				if (!guideUI && !advenUI)
					SCENE->ChangeScene("cSelectStageScene");
			}
			else if (MOUSE->Collider("guide_button") && MOUSE->Collider("guide_button", downPos))
			{
				if (!guideUI && !advenUI)
					guideUI = true;
			}
			else if (MOUSE->Collider("adven_button") && MOUSE->Collider("adven_button", downPos))
			{
				DebugParam(L"%d", SCENE->a_rewards[0]);
				if (!advenUI && !guideUI)
					advenUI = true;
			}
			else if (MOUSE->Collider("develop_button") && MOUSE->Collider("develop_button", downPos))
			{
				// 개발 노트 내용
			}
			else if (MOUSE->Collider("quit_button") && MOUSE->Collider("quit_button", downPos))
			{
				PostQuitMessage(0);
			}
		}
		if (MOUSE->Collider("guide_close") && MOUSE->Collider("guide_close", downPos))
		{
			if (guideUI)
			{
				guideUI = false;
				MOUSE->lUp = false;
			}
		}
		if (MOUSE->Collider("X"))
		{
			if (advenUI)
			{
				advenUI = false;
				MOUSE->lUp = false;
			}
		}
		if (MOUSE->Collider("Arrow") && !buttonsMoved)
		{
			buttonsMoved = true;
		}
	}
}

void cTitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(IMAGE->FindImage("Logo"), { logoPos.x, logoPos.y - temp }, 0.5);
	RENDER->CenterRender(IMAGE->FindImage("pattern"), { 500, 1000 - temp });

	RENDER->CenterRender(IMAGE->FindImage(arrowKey), Vec2(500, 2100 - temp), 1.5);

	MOUSE->Collider("start_button") ?
		MOUSE->lStay && MOUSE->Collider("start_button", downPos) ?
		RENDER->CenterRender(IMAGE->FindImage("click_Start"), Vec2(600, 250 - temp)) :
		RENDER->CenterRender(IMAGE->FindImage("over_Start"), Vec2(600, 250 - temp)) :
		tempFunc(0);

	MOUSE->Collider("guide_button") ?
		MOUSE->lStay && MOUSE->Collider("guide_button", downPos) ?
		RENDER->CenterRender(IMAGE->FindImage("click_Guide"), Vec2(600, 650 - temp)) :
		RENDER->CenterRender(IMAGE->FindImage("over_Guide"), Vec2(600, 650 - temp)) :
		tempFunc(1);
	MOUSE->Collider("adven_button") ?
		MOUSE->lStay && MOUSE->Collider("adven_button", downPos) ?
		RENDER->CenterRender(IMAGE->FindImage("click_Adven"), Vec2(600, 1050 - temp)) :
		RENDER->CenterRender(IMAGE->FindImage("over_Adven"), Vec2(600, 1050 - temp)) :
		tempFunc(2);

	MOUSE->Collider("develop_button") ?
		MOUSE->lStay && MOUSE->Collider("develop_button", downPos) ?
		RENDER->CenterRender(IMAGE->FindImage("click_Develop"), Vec2(600, 1450 - temp)) :
		RENDER->CenterRender(IMAGE->FindImage("over_Develop"), Vec2(600, 1450 - temp)) :
		tempFunc(3);

	MOUSE->Collider("quit_button") ?
		MOUSE->lStay && MOUSE->Collider("quit_button", downPos) ?
		RENDER->CenterRender(IMAGE->FindImage("click_Quit"), Vec2(600, 1850 - temp)) :
		RENDER->CenterRender(IMAGE->FindImage("over_Quit"), Vec2(600, 1850 - temp)) :
		tempFunc(4);

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
				RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1525, 450 * i), 0.3);
			}
		}

		for (int i = 1; i < 4; i++)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_ItemRect"), Vec2(2180, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentBG"), Vec2(2805, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_textBG"), Vec2(2805, 450 * i), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_ContentRect"), Vec2(2805, 450 * i), 0.3);
			if (SCENE->a_rewards[(i - 1) + 4] == 1)
				printf("heehee");
			else
			{
				RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(2180, 450 * i), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_Lock"), Vec2(2180, 450 * i + 40), 0.3);
				RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(2805, 450 * i), 0.3);
			}
		}

		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPerBG"), Vec2(350, WINSIZEY - 420), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CircleDown"), Vec2(350, WINSIZEY - 420), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CircleUp"), Vec2(350, WINSIZEY - 420), 0.5);
		RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPer"), Vec2(350, WINSIZEY - 420), 0.5);

		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(3330, WINSIZEY / 2 - 1023), 0.6);
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
