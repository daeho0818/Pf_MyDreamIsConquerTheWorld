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

	textCount = 1;
	percent = 0;
	timer = 180;
	CFCount = 0;
	speed = 100;
	delayCount = 0;
	SCENE->score = 0;
	SetHP(3);

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

	cTexture* ptr[2] = { IMAGE->FindImage("church_High"), IMAGE->FindImage("church_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cChurchScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cChurchScene::Update()
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

void cChurchScene::Render()
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

void cChurchScene::UIRender()
{
	player->UIRender();
	mob->UIRender();

	cParentScene::UIRender();
}

void cChurchScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}