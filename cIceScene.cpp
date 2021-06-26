#include "DXUT.h"
#include "cIceScene.h"

cIceScene::cIceScene()
{
}

cIceScene::~cIceScene()
{
	Release();
}

void cIceScene::Init()
{
	cParentScene::Init("cIceScene");

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
	IMAGE->DeleteImage("ice_High");
	IMAGE->DeleteImage("ice_Under");
	IMAGE->AddImage("ice_High", "Ingame/Ice/high");
	IMAGE->AddImage("ice_Under", "Ingame/Ice/under");
	cTexture* ptr[2] = { IMAGE->FindImage("ice_High"), IMAGE->FindImage("ice_Under") };
	t_BG = ptr[1];
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cIceScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cIceScene::Update()
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
			SCENE->m_rewards.find("Ice")->second = 1;
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

void cIceScene::Render()
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

void cIceScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cIceScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}