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

	IMAGE->DeleteImage("city(night)_High");
	IMAGE->DeleteImage("city(night)_Under");
	IMAGE->AddImage("city(night)_High", "Ingame/City(night)/high");
	IMAGE->AddImage("city(night)_Under", "Ingame/City(night)/under");

	cTexture* ptr[2] = { IMAGE->FindImage("city(night)_High"), IMAGE->FindImage("city(night)_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cCityNightScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;

	SOUND->StopAll();
	SOUND->Play("CityNight", DSBVOLUME_MAX, true);
}

void cCityNightScene::Update()
{
	cParentScene::Update();
}

void cCityNightScene::Render()
{
	cParentScene::Render();
}

void cCityNightScene::UIRender()
{
	cParentScene::UIRender();
}

void cCityNightScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	SOUND->Stop("CityNight");

	cParentScene::Release();
}