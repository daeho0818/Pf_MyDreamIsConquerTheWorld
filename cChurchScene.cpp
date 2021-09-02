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

	IMAGE->DeleteImage("church_High");
	IMAGE->DeleteImage("church_Under");
	IMAGE->AddImage("church_High", "Ingame/Church/high");
	IMAGE->AddImage("church_Under", "Ingame/Church/under");

	cTexture* ptr[2] = { IMAGE->FindImage("church_High"), IMAGE->FindImage("church_Under") };
	t_BG = ptr[1];

	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(player, bullet->m_bullets, "cChurchScene");
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);

	cParentScene::player = this->player;
	cParentScene::mob = this->mob;
	cParentScene::item = this->item;
	cParentScene::bullet = this->bullet;
	cParentScene::coll = this->coll;

	SOUND->StopAll();
	SOUND->Play("Church", DSBVOLUME_MAX, true);
}

void cChurchScene::Update()
{
	cParentScene::Update();
}

void cChurchScene::Render()
{
	cParentScene::Render();
}

void cChurchScene::UIRender()
{
	cParentScene::UIRender();
}

void cChurchScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);

	SOUND->Stop("Church");

	cParentScene::Release();
}