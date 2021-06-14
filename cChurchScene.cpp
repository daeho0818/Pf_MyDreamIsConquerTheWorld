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
	textCount = 1;
	percent = 0;
	timer = 180;
	CFCount = 0;
	speed = 100;
	delayCount = 0;
	hp = 3;
	SCENE->score = 0;

	isStart = false;
	isStop = false;
	isClear = false;
	isFail = false;
	isClearEnd = false;
	isFailEnd = false;
	delay = false;
	IMAGE->DeleteImage("church_High");
	IMAGE->DeleteImage("church_Under");
	IMAGE->AddImage("church_High", "Ingame/Church/high");
	IMAGE->AddImage("church_Under", "Ingame/Church/under");
	cTexture* ptr[2] = {IMAGE->FindImage("church_High"), IMAGE->FindImage("church_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cChurchScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cChurchScene::Update()
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

		if (player->coloring_per >= 80 || INPUT->KeyDown('G'))
		{
			isClear = true;
			SCENE->m_rewards.find("Church")->second = 1;
			DebugParam(L"%d", SCENE->m_rewards.find("Church")->second);
		}

		if (mob->isDestroy)
		{
			SCENE->score += 300;
			mob->isDestroy = false;
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