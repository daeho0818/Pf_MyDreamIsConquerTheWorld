#include "DXUT.h"
#include "cIngameScene2.h"

cIngameScene2::cIngameScene2()
{
}

cIngameScene2::~cIngameScene2()
{
	Release();
}

void cIngameScene2::Init()
{
	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	delay = false;
	isClearScene = false;
	AS = nullptr;
	t_Delay = nullptr;
	memset(Expl, 0, sizeof(Expl));
	IMAGE->DeleteImage("bg3");
	IMAGE->DeleteImage("bg4");
	IMAGE->AddImage("bg3", "bg3");
	IMAGE->AddImage("bg4", "bg4");
	cTexture* ptr[2] = { IMAGE->FindImage("bg3"), IMAGE->FindImage("bg4") };
	player = new cPlayer(ptr);
	mob = new cMobAdmin();
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_mobs, player, item);
}

void cIngameScene2::Update()
{
	if (AS != nullptr) AS->Update();
	if (t_Delay != nullptr) t_Delay->Update();
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
	mob->Update();
	item->Update();
	coll->Update();
	PrintStageTxt();
}

void cIngameScene2::Render()
{
	player->Render();
	mob->Render();
	item->Update();
	coll->Update();
}

void cIngameScene2::UIRender()
{
	player->UIRender();
	mob->UIRender();
	if (pos_x >= -50) UI->PrintText("STAGE 2", Vec2(pos_x, 50), 50);
	if (isClearScene) UI->PrintText("gameClear", { WINSIZEX / 2, WINSIZEY / 2 }, 100);
}

void cIngameScene2::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
	SAFE_DELETE(AS);
	SAFE_DELETE(t_Delay);
	for (int i = 0; i < 5; i++)
		SAFE_DELETE(Expl[i]);
}

void cIngameScene2::PrintStageTxt()
{
	if (left) pos_x -= 2; else if (right) pos_x += 2;

	if (pos_x > 200)
	{
		if (right) AS = new cTimer(2, [&]()->void {left = true; AS = nullptr; });
		right = false;
	}
}

void cIngameScene2::Explosion()
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