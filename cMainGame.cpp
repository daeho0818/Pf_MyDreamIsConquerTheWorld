#include "DXUT.h"
#include "cMainGame.h"
#include "cIntroScene.h"
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
	SCENE->AddScene("cIntroScene", new cIntroScene);
	SCENE->AddScene("cIngameScene", new cIngameScene);
	SCENE->AddScene("cIngameScene2", new cIngameScene2);
	SCENE->AddScene("cTitleScene", new cTitleScene);
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

	// guide
	IMAGE->AddImage("guide_BG", "title/GuideBook/BG");
	IMAGE->AddImage("guide_Arrow", "title/GuideBook/arrow");
	IMAGE->AddImage("guide_close", "title/GuideBook/close");
	IMAGE->AddImage("guide_text1", "title/GuideBook/text1");
	IMAGE->AddImage("guide_text2", "title/GuideBook/text2");

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
	IMAGE->AddImage("player", "player");
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