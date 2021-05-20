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
	IMAGE->AddImage("desert_High", "Ingame/Desert/desert_High");
	IMAGE->AddImage("desert_Under", "Ingame/Desert/desert_Under");
	cTexture* ptr[2] = {IMAGE->FindImage("desert_High"), IMAGE->FindImage("desert_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cDesertScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cDesertScene::Update()
{
	cParentScene::SetPercent(player->coloring_per);
	cParentScene::SetScore(SCENE->score);
	cParentScene::SetHP(player->hp);
	if (isStart)
	{
		if (timer <= 0 || player->hp <= 0)
		{
			isFail = true;
		}

		if (player->coloring_per >= 80/* || SCENE->Array[(int)mob->bossPos.x][(int)mob->bossPos.y]*/)
		{
			isClear = true;
		}
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