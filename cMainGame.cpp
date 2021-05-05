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
	SCENE->ChangeScene("cIntroScene");
}

void cMainGame::Update()
{
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
	IMAGE->AddImage("TitleBG", "TitleBG");
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

	IMAGE->AddImage("Logo", "Logo");
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

	IMAGE->AddImage("expl", "explosion/expl", 24);
}