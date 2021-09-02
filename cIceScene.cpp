#include "DXUT.h"
#include "cIceScene.h"

cIceScene::cIceScene()
{
}

cIceScene::~cIceScene()
{
	Release();
}

void cIceScene::Init()
{
	cParentScene::Init("cIceScene");

	IMAGE->DeleteImage("ice_High");
	IMAGE->DeleteImage("ice_Under");
	IMAGE->AddImage("ice_High", "Ingame/Ice/high");
	IMAGE->AddImage("ice_Under", "Ingame/Ice/under");

	cTexture* ptr[2] = { IMAGE->FindImage("ice_High"), IMAGE->FindImage("ice_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cIceScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;

	SOUND->StopAll();
	SOUND->Play("IceSelect", DSBVOLUME_MAX, true);
}

void cIceScene::Update()
{
	cParentScene::Update();
}

void cIceScene::Render()
{
	cParentScene::Render();
}

void cIceScene::UIRender()
{
	cParentScene::UIRender();
}

void cIceScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	SOUND->Stop("IceSelect");

	cParentScene::Release();
}