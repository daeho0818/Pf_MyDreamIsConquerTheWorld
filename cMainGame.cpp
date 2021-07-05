#include "DXUT.h"
#include "cMainGame.h"
#include "cTitleScene.h"
#include "cSelectStageScene.h"
#include "cIceScene.h"
#include "cCityScene.h"
#include "cCityNightScene.h"
#include "cChurchScene.h"
#include "cJungleScene.h"
#include "cDesertScene.h"
#include "cOceanScene.h"
#include "cEndScene.h"
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
	SCENE->AddScene("cTitleScene", new cTitleScene);
	SCENE->AddScene("cSelectStageScene", new cSelectStageScene);
	SCENE->AddScene("cIceScene", new cIceScene);
	SCENE->AddScene("cCityScene", new cCityScene);
	SCENE->AddScene("cCityNightScene", new cCityNightScene);
	SCENE->AddScene("cChurchScene", new cChurchScene);
	SCENE->AddScene("cDesertScene", new cDesertScene);
	SCENE->AddScene("cOceanScene", new cOceanScene);
	SCENE->AddScene("cJungleScene", new cJungleScene);
	SCENE->AddScene("cEndScene", new cEndScene);
	SCENE->ChangeScene("cLoadingScene");
}

void cMainGame::Update()
{
	MOUSE->Update();
	INPUT->Update();
	PART->Update();
	SCENE->Update();
	SOUND->Update();
	THREAD->Update();
	CAM->Update();
}

void cMainGame::Render()
{
	if (!BG->isLoadScene)
		BG->Render();
	PART->Render();
	SCENE->Render();
	UI->Begin();
	SCENE->UIRender();
	UI->End();
	CAM->Render();
}

void cMainGame::Release()
{
	cInputManager::ReleaseInstance();
	cParticleManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	cMouseManager::ReleaseInstance();
	cButtonManager::ReleaseInstance();
	cImageManager::ReleaseInstance();
	cThreadManager::ReleaseInstance();
	cBGManager::ReleaseInstance();
	cCameraManager::ReleaseInstance();
}

void cMainGame::ResetDevice()
{
	UI->Reset();
}

void cMainGame::LostDevice()
{
	UI->Lost();
}
