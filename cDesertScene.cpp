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

	IMAGE->DeleteImage("desert_High");
	IMAGE->DeleteImage("desert_Under");
	IMAGE->AddImage("desert_High", "Ingame/Desert/desert_high");
	IMAGE->AddImage("desert_Under", "Ingame/Desert/desert_under");

	cTexture* ptr[2] = { IMAGE->FindImage("desert_High"), IMAGE->FindImage("desert_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cDesertScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;

	SOUND->StopAll();
	SOUND->Play("Desert", DSBVOLUME_MAX, true);
}

void cDesertScene::Update()
{
	cParentScene::Update();
}

void cDesertScene::Render()
{

	cParentScene::Render();
}

void cDesertScene::UIRender()
{
	cParentScene::UIRender();
}

void cDesertScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	SOUND->Stop("Desert");

	cParentScene::Release();
}