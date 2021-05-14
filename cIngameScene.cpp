#include "DXUT.h"
#include "cIngameScene.h"

cIngameScene::cIngameScene()
{
}

cIngameScene::~cIngameScene()
{
	Release();
}

void cIngameScene::Init()
{
	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isClearScene = false;
	delay = false;
	AS = nullptr;
	t_Delay = nullptr;
	memset(Expl, 0, sizeof(Expl));
	IMAGE->DeleteImage("bg1");
	IMAGE->DeleteImage("bg2");
	IMAGE->AddImage("bg1", "bg1");
	IMAGE->AddImage("bg2", "bg2");
	cTexture* ptr[2] = { IMAGE->FindImage("bg1"), IMAGE->FindImage("bg2") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cIngameScene::Update()
{
	cParentScene::StageStart(&textPos[textCount - 1][0], &textPos[textCount - 1][0], &textPos[textCount - 1][1], 0.1);

	if (t_TextAni == nullptr)
	{
		if (textCount < 4)
		{
			t_TextAni = new cTimer(1, [&]()->void {
				t_TextAni = nullptr;
				textCount++;
				});
		}
	}
	if (AS != nullptr) AS->Update();
	if (t_Delay != nullptr) t_Delay->Update();
	if (t_TextAni != nullptr) t_TextAni->Update();
	if (delay)
	{
		if (t_Delay == nullptr)
		{
			t_Delay = new cTimer(3, [&]()->void {
				SCENE->ChangeScene("cIngameScene2");
				t_Delay = nullptr;
				});
		}
		player->stop = true;
		player->BG[0] = IMAGE->FindImage("bg2");
	}
	for (int i = 0; i < 5; i++) if (Expl[i] != nullptr) Expl[i]->Update();
	if (player->coloring_per >= 80 && !isClearScene)
	{
		isClearScene = true;
		Explosion();
		AS = new cTimer(1, [&]()->void {
			Explosion();
			delay = true;
			AS = nullptr;
			});
	}

	player->Update(mob->bossPos);
	bullet->Update();
	mob->Update();
	item->Update();
	coll->Update();
	PrintStageTxt();
}
void cIngameScene::Render()
{
	player->Render();
	bullet->Render();
	mob->Render();
	item->Render();
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
		//RENDER->CenterRender(IMAGE->FindImage("start_start"), textPos[3][0]);
		break;
	}
}

void cIngameScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
	if (pos_x >= -50) UI->PrintText("STAGE 1", Vec2(pos_x, 50), 50);
	if (delay) UI->PrintText("Game Clear!", { WINSIZEX / 2, WINSIZEY / 2 }, 100);
}

void cIngameScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
	SAFE_DELETE(AS);
	SAFE_DELETE(t_TextAni);
	SAFE_DELETE(t_Delay);
	for (int i = 0; i < 5; i++)
		SAFE_DELETE(Expl[i]);
}

void cIngameScene::PrintStageTxt()
{
	if (left) pos_x -= 2; else if (right) pos_x += 2;

	if (pos_x > 200)
	{
		if (right) AS = new cTimer(2, [&]()->void {left = true; AS = nullptr; });
		right = false;
	}
}

void cIngameScene::Explosion()
{
	Expl[0] = new cTimer((rand() % 1 / 10) * (rand() % 30), [&]()->void {
		PART->AddParticle({ float(rand() % 1400 + 50), float(rand() % 700 + 50) }, rand() % 30 + 15, 0, 0.005);
		Expl[0] = nullptr;
		});
	Expl[1] = new cTimer((rand() % 1 / 10) * (rand() % 50), [&]()->void {
		PART->AddParticle({ float(rand() % 1400 + 50), float(rand() % 700 + 50) }, rand() % 30 + 15, 0, 0.005);
		Expl[1] = nullptr;
		});
	Expl[2] = new cTimer((rand() % 1 / 10) * (rand() % 40), [&]()->void {
		PART->AddParticle({ float(rand() % 1400 + 50), float(rand() % 700 + 50) }, rand() % 30 + 15, 0, 0.005);
		Expl[2] = nullptr;
		});
	Expl[3] = new cTimer((rand() % 1 / 10) * (rand() % 20), [&]()->void {
		PART->AddParticle({ float(rand() % 1400 + 50), float(rand() % 700 + 50) }, rand() % 30 + 15, 0, 0.005);
		Expl[3] = nullptr;
		});
	Expl[4] = new cTimer((rand() % 1 / 10) * (rand() % 60), [&]()->void {
		PART->AddParticle({ float(rand() % 1400 + 50), float(rand() % 700 + 50) }, rand() % 30 + 15, 0, 0.005);
		Expl[4] = nullptr;
		});
}
