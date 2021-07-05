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

	pos_x = 0;
	textCount = 1;
	percent = 0;
	timer = 180;
	CFCount = 0;
	speed = 100;
	delayCount = 0;
	SCENE->score = 0;
	SetHP(3);

	left = false; right = true;
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

	cTexture* ptr[2] = { IMAGE->FindImage("city(night)_High"), IMAGE->FindImage("city(night)_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cCityNightScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cCityNightScene::Update()
{
	SetPercent(player->coloring_per);
	SetScore(SCENE->score);
	SetHP(player->hp);
	SetBossPos(mob->bossPos);

	if (isStart)
	{
		if (timer <= 0 || player->hp <= 0)
		{
			isFail = true;
		}

		if (player->coloring_per >= 80 || INPUT->KeyDown('G'))
		{
			isClear = true;
		}

		if (mob->isDestroy)
		{
			SCENE->score += 300;
			mob->isDestroy = false;
		}
	}

	mob->Animation();
	player->CamEvent();
	if (isStart && !isStop)
	{
		mob->Update();
		if (!isClear && !isFail)
		{
			player->Update(mob->bossPos);
			bullet->Update();
			item->Update();
			coll->Update();
		}
	}

	cParentScene::Update();
}

void cCityNightScene::Render()
{
	if (isStart && !isStop && !isClear && !isFail)
	{
		bullet->Render();
		item->Render();
	}
	player->Render();
	mob->Render();
	cParentScene::Render();
}

void cCityNightScene::UIRender()
{
	player->UIRender();
	mob->UIRender();

	cParentScene::UIRender();
}

void cCityNightScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}