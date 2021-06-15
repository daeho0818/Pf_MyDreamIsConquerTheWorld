#include "DXUT.h"
#include "cCityNightScene.h"

cCityNightScene::cCityNightScene()
{
}

cCityNightScene::~cCityNightScene()
{
	Release();
}

void cCityNightScene::Init()
{
	cParentScene::Init("cCityNightScene");

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
	IMAGE->DeleteImage("city(night)_High");
	IMAGE->DeleteImage("city(night)_Under");
	IMAGE->AddImage("city(night)_High", "Ingame/City(night)/high");
	IMAGE->AddImage("city(night)_Under", "Ingame/City(night)/under");
	cTexture* ptr[2] = {IMAGE->FindImage("city(night)_High"), IMAGE->FindImage("city(night)_Under") };
	BG = ptr[1];
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cCityNightScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cCityNightScene::Update()
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
			SCENE->m_rewards.find("CityNight")->second = 1;
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

void cCityNightScene::Render()
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

void cCityNightScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cCityNightScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}