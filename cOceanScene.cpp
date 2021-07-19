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

	IMAGE->DeleteImage("ocean_High");
	IMAGE->DeleteImage("ocean_Under");
	IMAGE->AddImage("ocean_High", "Ingame/Ocean/high");
	IMAGE->AddImage("ocean_Under", "Ingame/Ocean/under");

	cTexture* ptr[2] = { IMAGE->FindImage("ocean_High"), IMAGE->FindImage("ocean_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cOceanScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;
}

void cOceanScene::Update()
{
	cParentScene::Update();
}

void cOceanScene::Render()
{
	cParentScene::Render();
}

void cOceanScene::UIRender()
{
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