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
	cParentScene::Init();

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	AS = nullptr;
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
	if (player->coloring_per >= 80)
	{
		isClear = true;
		cParentScene::SetPercent(player->coloring_per);
		//cParentScene::SetScore(player->score);
	}

	if (isStart && !isStop)
	{
		player->Update(mob->bossPos);
		bullet->Update();
		mob->Update();
		item->Update();
		coll->Update();
	}
	PrintStageTxt();

	if (INPUT->KeyDown(VK_ESCAPE)) isStop = !isStop;

	cParentScene::Update();
}

void cIngameScene::Render()
{
	player->Render();
	if (isStart && !isStop)
	{
		bullet->Render();
		mob->Render();
		item->Render();
	}
	cParentScene::Render();
}

void cIngameScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
	if (pos_x >= -50) UI->PrintText("STAGE 1", Vec2(pos_x, 50), 50);
}

void cIngameScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
	SAFE_DELETE(AS);
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
