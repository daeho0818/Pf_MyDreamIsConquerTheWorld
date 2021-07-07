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

	IMAGE->DeleteImage("city_High");
	IMAGE->DeleteImage("city_Under");
	IMAGE->AddImage("city_High", "Ingame/City/high");
	IMAGE->AddImage("city_Under", "Ingame/City/under");

	cTexture* ptr[2] = { IMAGE->FindImage("city_High"), IMAGE->FindImage("city_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets, "cCityScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;
}

void cCityScene::Update()
{
	cParentScene::Update();
}

void cCityScene::Render()
{
	cParentScene::Render();
}

void cCityScene::UIRender()
{
	cParentScene::UIRender();
}

void cCityScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	cParentScene::Release();
}
