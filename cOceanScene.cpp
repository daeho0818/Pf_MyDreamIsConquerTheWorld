#include "DXUT.h"
#include "cOceanScene.h"

cOceanScene::cOceanScene()
{
}

cOceanScene::~cOceanScene()
{
	Release();
}

void cOceanScene::Init()
{
	cParentScene::Init("cOceanScene");

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	IMAGE->DeleteImage("ocean_High");
	IMAGE->DeleteImage("ocean_Under");
	IMAGE->AddImage("ocean_High", "Ingame/Ocean/high");
	IMAGE->AddImage("ocean_Under", "Ingame/Ocean/under");
	cTexture* ptr[2] = {IMAGE->FindImage("ocean_High"), IMAGE->FindImage("ocean_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cOceanScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cOceanScene::Update()
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

	cParentScene::Update();
}

void cOceanScene::Render()
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

void cOceanScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cOceanScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}