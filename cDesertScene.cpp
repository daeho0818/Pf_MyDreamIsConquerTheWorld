#include "DXUT.h"
#include "cDesertScene.h"

cDesertScene::cDesertScene()
{
}

cDesertScene::~cDesertScene()
{
	Release();
}

void cDesertScene::Init()
{
	cParentScene::Init("cDesertScene");

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	IMAGE->DeleteImage("desert_High");
	IMAGE->DeleteImage("desert_Under");
	IMAGE->AddImage("desert_High", "Ingame/Desert/high");
	IMAGE->AddImage("desert_Under", "Ingame/Desert/under");
	cTexture* ptr[2] = {IMAGE->FindImage("desert_High"), IMAGE->FindImage("desert_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cDesertScene::Update()
{
	if (player->timer <= 0)
	{
		isFail = true;
		cParentScene::SetPercent(player->coloring_per);
		//cParentScene::SetScore(player->score);
	}

	if (player->coloring_per >= 80)
	{
		isClear = true;
		cParentScene::SetPercent(player->coloring_per);
		//cParentScene::SetScore(player->score);
	}

	if (isStart && !isStop && !isClear && !isFail)
	{
		player->Update(mob->bossPos);
		bullet->Update();
		mob->Update();
		item->Update();
		coll->Update();
	}

	if (INPUT->KeyDown(VK_ESCAPE)) isStop = !isStop;

	cParentScene::Update();
}

void cDesertScene::Render()
{
	player->Render();
	if (isStart && !isStop && !isClear && !isFail)
	{
		bullet->Render();
		mob->Render();
		item->Render();
	}
	cParentScene::Render();
}

void cDesertScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cDesertScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}