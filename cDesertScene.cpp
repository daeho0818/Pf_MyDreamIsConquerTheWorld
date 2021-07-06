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

	IMAGE->DeleteImage("desert_High");
	IMAGE->DeleteImage("desert_Under");
	IMAGE->AddImage("desert_High", "Ingame/Desert/desert_high");
	IMAGE->AddImage("desert_Under", "Ingame/Desert/desert_under");

	cTexture* ptr[2] = { IMAGE->FindImage("desert_High"), IMAGE->FindImage("desert_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cDesertScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cDesertScene::Update()
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

		if (mob->isDestroy)
		{
			SCENE->score += 300;
			mob->isDestroy = false;
		}
	}

	mob->Animation();
	player->CamEvent();
	if (isStart && !isdead && !isStop)
	{
		if (!isClear && !isFail)
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

void cDesertScene::Render()
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

void cDesertScene::UIRender()
{
	player->UIRender();
	mob->UIRender();

	cParentScene::UIRender();
}

void cDesertScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}