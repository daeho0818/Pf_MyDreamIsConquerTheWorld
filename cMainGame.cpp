#include "DXUT.h"
#include "cMainGame.h"
#include "cSelectStageScene.h"
#include "cIngameScene.h"
#include "cIngameScene2.h"
#include "cTitleScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	AddResource();
	SCENE->AddScene("cTitleScene", new cTitleScene);
	SCENE->AddScene("cSelectStageScene", new cSelectStageScene);
	SCENE->AddScene("cIngameScene", new cIngameScene);
	SCENE->AddScene("cIngameScene2", new cIngameScene2);
	SCENE->ChangeScene("cTitleScene");
}

void cMainGame::Update()
{
	MOUSE->Update();
	INPUT->Update();
	PART->Update();
	SCENE->Update();
	SOUND->Update();
}

void cMainGame::Render()
{
	SCENE->Render();
	PART->Render();
	UI->Begin();
	SCENE->UIRender();
	UI->End();
}

void cMainGame::Release()
{
	cImageManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
	cParticleManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	cMouseManager::ReleaseInstance();
	cButtonManager::ReleaseInstance();
}

void cMainGame::ResetDevice()
{
	UI->Reset();
}

void cMainGame::LostDevice()
{
	UI->Lost();
}

void cMainGame::AddResource()
{
	// title
	IMAGE->AddImage("TitleBG", "title/TitleBG");
	IMAGE->AddImage("Logo", "title/Logo");
	IMAGE->AddImage("start_note", "title/start_note");
	IMAGE->AddImage("start_button", "title/start_button");
	IMAGE->AddImage("guide_note", "title/guide_note");
	IMAGE->AddImage("guide_button", "title/guide_button");
	IMAGE->AddImage("adven_note", "title/adven_note");
	IMAGE->AddImage("adven_button", "title/adven_button");
	IMAGE->AddImage("develop_note", "title/develop_note");
	IMAGE->AddImage("develop_button", "title/develop_button");
	IMAGE->AddImage("quit_note", "title/quit_note");
	IMAGE->AddImage("quit_button", "title/quit_button");
	IMAGE->AddImage("pattern", "title/pattern");

	// guide Note
	IMAGE->AddImage("guide_BG", "title/GuideBook/BG");
	IMAGE->AddImage("guide_Arrow", "title/GuideBook/arrow");
	IMAGE->AddImage("guide_close", "title/GuideBook/close");
	IMAGE->AddImage("guide_text1", "title/GuideBook/text1");
	IMAGE->AddImage("guide_text2", "title/GuideBook/text2");

	//adventure Note
	IMAGE->AddImage("adven_Back", "title/AdvenBook/back");
	IMAGE->AddImage("adven_BG", "title/AdvenBook/BG");
	IMAGE->AddImage("adven_BGRect", "title/AdvenBook/BGRect");
	IMAGE->AddImage("adven_Chain", "title/AdvenBook/chains");
	IMAGE->AddImage("adven_Lock", "title/AdvenBook/lock");
	IMAGE->AddImage("adven_CircleDown", "title/AdvenBook/circleDown");
	IMAGE->AddImage("adven_CircleUp", "title/AdvenBook/circleUp");
	IMAGE->AddImage("adven_CollectionPer", "title/AdvenBook/collectionPer");
	IMAGE->AddImage("adven_CollectionPerBG", "title/AdvenBook/collectionPerBG");
	IMAGE->AddImage("adven_CollectionPerRect", "title/AdvenBook/collectionPerRect");
	IMAGE->AddImage("adven_ContentRect", "title/AdvenBook/contentRect");
	IMAGE->AddImage("adven_ContentBG", "title/AdvenBook/contentBG");
	IMAGE->AddImage("adven_Handle", "title/AdvenBook/handle");
	IMAGE->AddImage("adven_HandleBG", "title/AdvenBook/handleBG");
	IMAGE->AddImage("adven_ItemRect", "title/AdvenBook/itemRect");

	// world map
	IMAGE->AddImage("WorldMap", "WorldMap/map");
	IMAGE->AddImage("WorldEmblem", "WorldMap/Emblem");
	IMAGE->AddImage("church_button", "WorldMap/church_button");
	IMAGE->AddImage("church_complete", "WorldMap/church_complete");
	IMAGE->AddImage("church_lock", "WorldMap/church_lock");
	IMAGE->AddImage("city(night)_button", "WorldMap/city(night)_button");
	IMAGE->AddImage("city(night)_complete", "WorldMap/city(night)_complete");
	IMAGE->AddImage("city(night)_lock", "WorldMap/city(night)_lock");
	IMAGE->AddImage("city_button", "WorldMap/city_button");
	IMAGE->AddImage("city_complete", "WorldMap/city_complete");
	IMAGE->AddImage("city_lock", "WorldMap/city_lock");
	IMAGE->AddImage("desert_button", "WorldMap/desert_button");
	IMAGE->AddImage("desert_complete", "WorldMap/desert_complete");
	IMAGE->AddImage("desert_lock", "WorldMap/desert_lock");
	IMAGE->AddImage("ice_button", "WorldMap/ice_button");
	IMAGE->AddImage("ice_complete", "WorldMap/ice_complete");
	IMAGE->AddImage("ice_lock", "WorldMap/ice_lock");
	IMAGE->AddImage("jungle_button", "WorldMap/jungle_button");
	IMAGE->AddImage("jungle_complete", "WorldMap/jungle_complete");
	IMAGE->AddImage("jungle_lock", "WorldMap/jungle_lock");
	IMAGE->AddImage("ocean_button", "WorldMap/ocean_button");
	IMAGE->AddImage("ocean_complete", "WorldMap/ocean_complete");
	IMAGE->AddImage("ocean_lock", "WorldMap/ocean_lock");

	// ingame
	IMAGE->AddImage("player", "Ingame/player");
	IMAGE->AddImage("start_1", "Ingame/Start/1");
	IMAGE->AddImage("start_2", "Ingame/Start/2");
	IMAGE->AddImage("start_3", "Ingame/Start/3");
	IMAGE->AddImage("start_start", "Ingame/Start/start");

	IMAGE->AddImage("Blur", "Blur");

	IMAGE->AddImage("Start", "Start");
	IMAGE->AddImage("hStart", "hStart");
	IMAGE->AddImage("HowTo", "HowTo");
	IMAGE->AddImage("hHowTo", "hHowTo");
	IMAGE->AddImage("End", "End");
	IMAGE->AddImage("hEnd", "hEnd");
	IMAGE->AddImage("goIntro", "goIntro");
	IMAGE->AddImage("hgoIntro", "hgoIntro");

	IMAGE->AddImage("bg3", "bg3");
	IMAGE->AddImage("bg4", "bg4");
	IMAGE->AddImage("Boss", "Boss");

	IMAGE->AddImage("intro1", "intro1");
	IMAGE->AddImage("intro2", "intro2");
	IMAGE->AddImage("intro3", "intro3");
	IMAGE->AddImage("HowToUI", "HowToUI");

	IMAGE->AddImage("fireEffect", "fireEffect");
	IMAGE->AddImage("angelEffect", "angelEffect");
	IMAGE->AddImage("badEffect", "badEffect");

	IMAGE->AddImage("hpBar", "hpBar");
	IMAGE->AddImage("Hp+", "Hp+");
	IMAGE->AddImage("Speed+", "Speed+");
	IMAGE->AddImage("Invincibility", "Invincibility");

	IMAGE->AddImage("bullet_enemy", "bullet_enemy");

	IMAGE->AddImage("expl", "explosion/expl", 24);
}