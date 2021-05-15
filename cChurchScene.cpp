#include "DXUT.h"
#include "cChurchScene.h"

cChurchScene::cChurchScene()
{
}

cChurchScene::~cChurchScene()
{
	Release();
}

void cChurchScene::Init()
{
	cParentScene::Init("cChurchScene");

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	IMAGE->DeleteImage("church_High");
	IMAGE->DeleteImage("church_Under");
	IMAGE->AddImage("church_High", "Ingame/Church/high");
	IMAGE->AddImage("church_Under", "Ingame/Church/under");
	cTexture* ptr[2] = {IMAGE->FindImage("church_High"), IMAGE->FindImage("church_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cChurchScene::Update()
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

void cChurchScene::Render()
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

void cChurchScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cChurchScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}