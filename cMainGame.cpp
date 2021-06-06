#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadingScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	SCENE->AddScene("cLoadingScene", new cLoadingScene);
	SCENE->ChangeScene("cLoadingScene");
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
