#include "DXUT.h"
#include "cJungleScene.h"

cJungleScene::cJungleScene()
{
}

cJungleScene::~cJungleScene()
{
	Release();
}

void cJungleScene::Init()
{
	cParentScene::Init("cJungleScene");

	IMAGE->DeleteImage("jungle_High");
	IMAGE->DeleteImage("jungle_Under");
	IMAGE->AddImage("jungle_High", "Ingame/Jungle/high");
	IMAGE->AddImage("jungle_Under", "Ingame/Jungle/under");

	cTexture* ptr[2] = { IMAGE->FindImage("jungle_High"), IMAGE->FindImage("jungle_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cJungleScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;
}

void cJungleScene::Update()
{
	cParentScene::Update();
}

void cJungleScene::Render()
{
	cParentScene::Render();
}

void cJungleScene::UIRender()
{
	cParentScene::UIRender();
}

void cJungleScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}