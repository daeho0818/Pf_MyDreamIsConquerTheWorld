#include "DXUT.h"
#include "cCityScene.h"

cCityScene::cCityScene()
{
}

cCityScene::~cCityScene()
{
	Release();
}

void cCityScene::Init()
{
	cParentScene::Init("cCityScene");
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
	IMAGE->DeleteImage("city_High");
	IMAGE->DeleteImage("city_Under");
	IMAGE->AddImage("city_High", "Ingame/City/high");
	IMAGE->AddImage("city_Under", "Ingame/City/under");
	cTexture* ptr[2] = { IMAGE->FindImage("city_High"), IMAGE->FindImage("city_Under") };
	BG = ptr[1];
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cCityScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cCityScene::Update()
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
			SCENE->m_rewards.find("City")->second = 1;
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

void cCityScene::Render()
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

void cCityScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cCityScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}
