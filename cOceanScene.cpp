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

	IMAGE->DeleteImage("ocean_High");
	IMAGE->DeleteImage("ocean_Under");
	IMAGE->AddImage("ocean_High", "Ingame/Ocean/high");
	IMAGE->AddImage("ocean_Under", "Ingame/Ocean/under");

	cTexture* ptr[2] = { IMAGE->FindImage("ocean_High"), IMAGE->FindImage("ocean_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cOceanScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cOceanScene::Update()
{
	SetPercent(player->coloring_per);
	SetScore(SCENE->score);
	SetHP(player->hp);
	SetBossPos(mob->bossPos);
	SetPlayerPos(player->m_pos);

	if (isStart)
	{
		if (timer <= 0 || player->hp <= 0 || INPUT->KeyDown('H'))
		{
			player->hp = 0;
			isdead = true;
			PlayerDead(player);
		}

		if (player->coloring_per >= 80 || INPUT->KeyDown('G'))
		{
			isClear = true;
		}
	}

	if (mob->isDestroy)
	{
		SCENE->score += 300;
		mob->isDestroy = false;
	}

	mob->Animation();
	player->CamEvent();
	if (isStart && !isStop)
	{
		if (!isClear && !isdead && !isFail)
		{
			mob->Update();
			player->Update(mob->bossPos);
			bullet->Update();
			item->Update();
			coll->Update();
		}
	}

	cParentScene::Update();
}

void cOceanScene::Render()
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

void cOceanScene::UIRender()
{
	player->UIRender();
	mob->UIRender();

	cParentScene::UIRender();
}

void cOceanScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}