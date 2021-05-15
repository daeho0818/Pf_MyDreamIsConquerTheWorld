#include "DXUT.h"
#include "cJungleScene.h"

cJungleScene::cJungleScene()
{
}

cJungleScene::~cJungleScene()
{
	Release();
}

void cJungleScene::Init()
{
	cParentScene::Init("cJungleScene");

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	IMAGE->DeleteImage("jungle_High");
	IMAGE->DeleteImage("jungle_Under");
	IMAGE->AddImage("jungle_High", "Ingame/Jungle/high");
	IMAGE->AddImage("jungle_Under", "Ingame/Jungle/under");
	cTexture* ptr[2] = {IMAGE->FindImage("jungle_High"), IMAGE->FindImage("jungle_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cJungleScene::Update()
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

void cJungleScene::Render()
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

void cJungleScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cJungleScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}